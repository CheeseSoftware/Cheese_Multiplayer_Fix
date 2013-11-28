#include "World.h"
#include "App.h"
#include "TextureContainer.h"
#include "Camera.h"
#include "Chunk.h"
#include "BlockSolid.h"
#include "BlockBackground.h"
#include "BlockGravity.h"
#include "Player.h"
#include "MessageType.h"
#include "EventHandler.h"
#include "GameUtility.h"
#include <deque>
#include <mutex>
#include <typeinfo>

#define getChunkMatrixIndexX(x) (int)abs(x>>4 + chunkMatrix.second)
#define getChunkColumnIndexY(y,x_it) (int)abs(y>>4 + x_it.second)
#define isColumnInsideChunkMatrix(x) x >= 0 && x < chunkMatrix.first.size()
#define isChunkInsideChunkColumn(y,x_it) y >= 0 && y < x_it.size()
World::World(GameUtility *gameUtility)
	: physicBlock(gameUtility->getBlockRegister().getBlockType(3), 3)
{

}

#ifndef _SERVER
void World::EventUpdate(App &app, const sf::Event &event, GameUtility *gameUtility)
{
	eventHandler.EventUpdate(app, event, gameUtility);
}

void World::Draw(App &app, GameUtility *gameUtility) // >.<
{
	sf::Sprite background = gameUtility->getTextureContainer().getTextures("Background.png")[0];
	for(int x = 0; x <= app.getSize().x / 512; x++)
	{
		for(int y = 0; y <= app.getSize().y / 512; y++)
		{
			background.setPosition(gameUtility->getCamera().getLeftX() + 512*x, gameUtility->getCamera().getTopY() + 512*y);
			app.draw(background);
		}
	}
	int minX = (int)gameUtility->getCamera().getLeftX()-255>>8;
	int minY = (int)gameUtility->getCamera().getTopY()-255>>8;
	int maxX = INT_MAX;
	int maxY;

	minX = (minX < 0)? 0 : minX;
	minY = (minY < 0)? 0 : minY;
	maxX = (maxX < chunkMatrix.first.size())? maxX : chunkMatrix.first.size();

	for (int x = minX; x < maxX; x++)
	{
		maxY = INT_MAX;
		maxY = (maxY < chunkMatrix.first[x].first.size())?
maxY : chunkMatrix.first[x].first.size();

		for (int y = minY; y < maxY; y++)
		{
			if (chunkMatrix.first[x].first[y] != nullptr)
			{
				chunkMatrix.first[x].first[y]->Draw(x-chunkMatrix.second, y-chunkMatrix.first[x].second, app, gameUtility);
			}
		}
	}



	entityListLock.lock();
	for (Entity *entity : entityList)
	{
		entity->Draw(app, gameUtility);
	}
	entityListLock.unlock();

	creatureListLock.lock();
	for(std::pair<short, Creature*> pair : creatureList)
	{
		pair.second->Draw(app, gameUtility);
	}
	creatureListLock.unlock();
}
#endif

void World::Update(App &app, GameUtility *gameUtility)
{
	for (Entity *entity : entityList)
	{
#ifdef _SERVER
		entity->Update(app, gameUtility);
#else
		entity->Update(app, gameUtility);
#endif
	}

	std::vector<short> toRemove = std::vector<short>();
	for(std::pair<short, Creature*> pair : creatureList)
	{
#ifdef _SERVER
		pair.second->Update(app, gameUtility);
#else
		pair.second->Update(app, gameUtility);
#endif
		if(pair.second->isDead())
		{
			sf::Packet packet;
			packet << (sf::Uint16)PlayerRespawn << (sf::Uint16)pair.first << (sf::Int32)0 << (sf::Int32)0;
			gameUtility->SendPacket(packet);
			pair.second->setHealth(100);
		}
	}
	for(short id : toRemove)
	{
		RemoveCreature(id);
	}
}

void World::setBlock(long x, long y, long layer, unsigned short id, GameUtility *gameUtility)
{
	setBlockAndMetadata(x, y, layer, id, 0, gameUtility);
}

void World::SendSetBlockAndMetadata(long x, long y, long layer, unsigned short id, unsigned short metadata, GameUtility *gameUtility) //Only sends the block change
{
	MessageType messageType = getBlockPacket(x, y, layer, id, metadata, gameUtility);

	sf::Packet *packet = new sf::Packet();
	*packet << (sf::Uint16)messageType;

	if(id != 0)
		gameUtility->getBlockRegister().getBlockType(id)->OnSend(packet, messageType, x, y, layer, id, metadata, gameUtility);
	else
		*packet << (sf::Uint16)id << (sf::Int32)x << (sf::Int32)y << (sf::Uint16)layer << (sf::Uint16)metadata;
	gameUtility->SendPacket(*packet);
}

void World::setBlockAndMetadata(long x, long y, long layer, unsigned short id, unsigned short metadata, GameUtility *gameUtility) //Sets block and sends the block change
{
	MessageType messageType = setBlockAndMetadataLocal(x, y, layer, id, metadata, gameUtility);

	sf::Packet *packet = new sf::Packet();
	*packet << (sf::Uint16)messageType;

	if(id != 0)
		gameUtility->getBlockRegister().getBlockType(id)->OnSend(packet, messageType, x, y, layer, id, metadata, gameUtility);
	else
		*packet << (sf::Uint16)id << (sf::Int32)x << (sf::Int32)y << (sf::Uint16)layer << (sf::Uint16)metadata;
	gameUtility->SendPacket(*packet);
}

MessageType World::getBlockPacket(long x, long y, long layer, unsigned short id, unsigned short metadata, GameUtility *gameUtility)
{
	long xx = floor(x * 0.0625)+1;

	unsigned short xxx = x&0xF;
	unsigned short yyy = y&0xF;

	Expand(xx, 0, nullptr);
	long yy = floor(y * 0.0625)+1;
	Expand(xx, yy, nullptr);

	auto &it = chunkMatrix.first.at(xx + chunkMatrix.second);
	Chunk* c = it.first.at(yy + it.second);
	if (c == nullptr)
	{
		if (id == 0)
			return NullMessage;

		c = it.first.at(yy + it.second) = new Chunk();
	}
	else
	{
		Block *block = c->getBlock(layer, xxx, yyy);
		if (block != nullptr)
		{
			if (gameUtility->getBlockRegister().getBlockIdByTypeId(typeid(*block).hash_code()) == id)
			{
				if (c->getMetadata(layer, xxx, yyy) != metadata)
				{
					//c->setMetadata(layer, xxx, yyy, metadata);
					return BlockMetadataChange;
				}
				return NullMessage;
			}
		}
		else if (id == 0)
			return NullMessage;
	}
	//c->setBlock(layer, xxx, yyy, gameUtility->getBlockRegister().getBlockType(id));
	//c->setMetadata(layer, xxx, yyy, metadata);
	return BlockPlace;
}

void World::setBlockMetadata(long x, long y, long layer, unsigned short metadata, GameUtility *gameUtility)
{
	if (setBlockMetadataLocal(x, y, layer, metadata, gameUtility) == BlockMetadataChange)
	{
		sf::Packet packet;
		packet << (sf::Int16)BlockMetadataChange << (sf::Int32)x << (sf::Int32)y << (sf::Uint16)layer << (sf::Uint16)metadata;
		gameUtility->SendPacket(packet);
	}
}

MessageType World::setBlockAndMetadataLocal(long x, long y, long layer, unsigned short id, unsigned short metadata, GameUtility *gameUtility)
{
	long xx = floor(x * 0.0625)+1;

	unsigned short xxx = x&0xF;
	unsigned short yyy = y&0xF;

	Expand(xx, 0, nullptr);
	long yy = floor(y * 0.0625)+1;
	Expand(xx, yy, nullptr);

	auto &it = chunkMatrix.first.at(xx + chunkMatrix.second);
	Chunk* c = it.first.at(yy + it.second);
	if (c == nullptr)
	{
		if (id == 0)
		{

			return NullMessage;
		}

		c = it.first.at(yy + it.second) = new Chunk();
	}
	else
	{
		Block *block = c->getBlock(layer, xxx, yyy);
		if (block != nullptr)
		{
			if (gameUtility->getBlockRegister().getBlockIdByTypeId(typeid(*block).hash_code()) == id)
			{
				if (c->getMetadata(layer, xxx, yyy) != metadata)
				{
					c->setMetadata(layer, xxx, yyy, metadata);

					return BlockMetadataChange;
				}


				return NullMessage;
			}
		}
		else if (id == 0)
		{

			return NullMessage;
		}
	}

	c->setBlock(layer, xxx, yyy, gameUtility->getBlockRegister().getBlockType(id));
	c->setMetadata(layer, xxx, yyy, metadata);

	return BlockPlace;
}

MessageType World::setBlockMetadataLocal(long x, long y, long layer, unsigned short metadata, GameUtility *gameUtility)
{

	unsigned short xxx = x&0xF;
	unsigned short yyy = y&0xF;

	long xx = floor(x * 0.0625)+1;
	if (isColumnInsideChunkMatrix(xx))
	{
		auto &it = chunkMatrix.first.at(xx);
		long yy = floor(y * 0.0625)+1;
		if (isChunkInsideChunkColumn(yy,it.first))
		{
			Chunk *c = it.first.at(yy);

			if (c != nullptr)
			{
				if (c->getMetadata(layer, xxx, yyy) != metadata)
				{
					std::cout << "set metadata at layer:" << layer << " X:" << xxx << " Y:" << yyy << " to:" << metadata << std::endl;
					c->setMetadata(layer, xxx, yyy, metadata);
					return BlockMetadataChange;
				}
			}
		}
	}
	//std::cout << "chunkmatrix unlocked!\n";
	return NullMessage;
}

Block *World::getBlock(long x, long y, long layer)
{
	Block *block = getBlockAndMetadata(x, y, layer).first;
	return block;
}

std::pair<Block*, unsigned short> World::getBlockAndMetadata(long x, long y, long layer)
{
	// //std::cout << "chunkmatrix locked!\n";
	if (lastBlock.first._Equals(std::tuple<long, long, short>(x, y, layer)))
	{
		//	 //std::cout << "chunkmatrix unlocked!\n";
		return *lastBlock.second;
	}

	long xx = floor(x * 0.0625) + chunkMatrix.second+1;

	unsigned short xxx = x&0xF;
	unsigned short yyy = y&0xF;

	if (isColumnInsideChunkMatrix(xx))
	{
		auto it = chunkMatrix.first.at(xx);
		long yy = floor(y * 0.0625) + it.second+1;

		if (isChunkInsideChunkColumn(yy,it.first))
		{
			if (it.first.at(yy) != nullptr)
			{
				Chunk* chunk = it.first.at(yy);//->getBlock(layer, xxx, yyy);
				// //std::cout << "chunkmatrix unlocked!\n";
				return *(lastBlock = std::pair<std::tuple<long, long, unsigned short>, 
					std::pair<Block*, unsigned short>*>
					(std::tuple<long, long, unsigned short>(x, y, layer),
					&chunk->getBlockAndMetadata(xxx, yyy, layer))).second;
				//std::pair<Block*, unsigned short>(chunk->getBlock(layer, xxx, yyy), chunk->getMetadata(layer, xxx, yyy));
			}
		}
	}
	// //std::cout << "chunkmatrix unlocked!\n";
	return std::pair<Block*, unsigned short>(nullptr, 0);
}

const std::pair<Block*, unsigned short> World::getPhysicBlock() const
{
	return physicBlock;
}

void World::Expand(long x, long y, Chunk* chunk)
{
	// //std::cout << "chunkmatrix locked!\n";
	//std::cout << sizeof(int);
	long xx = x + chunkMatrix.second;
	if (xx < 0)
	{
		for (long i = xx; i < 0; i++)
		{
			//std::cout << "XD\n";
			chunkMatrix.first.push_front(ChunkColumnType(std::deque<Chunk*>(),0));
			chunkMatrix.second++;
			//std::cout << "XD XD XD\n";
		}
		xx = x + chunkMatrix.second;
	}
	else if (xx >= chunkMatrix.first.size())
	{
		for (long i = 0; i <= xx; i++)
		{
			chunkMatrix.first.push_back(ChunkColumnType(std::deque<Chunk*>(),0));
		}
	}

	ChunkColumnType& it = chunkMatrix.first.at(xx);
	long yy = y + it.second;

	if (yy < 0)
	{
		for (long i = yy; i < 0; i++)
		{
			it.first.push_front(nullptr);
			it.second++;
		}
		yy = y + it.second;
	}
	else if (yy >= it.first.size())
	{
		for (long i = 0; i <= yy; i++)
		{
			it.first.push_back(nullptr);
		}
	}

	// //std::cout << "chunkmatrix unlocked!\n";
}

int World::AddEntity(Entity *entity)
{
	entityListLock.lock(); //std::cout << "entitylist locked!\n";
	entityList.push_back(entity);
	CLIENT(
		//eventHandler.AddEventCallback(entity,[entity] (App& a, const sf::Event& e, GameState* gUtil) { entity->EventUpdate(a, e, reinterpret_cast<GameUtility*>(gUtil)); });
		)
		entityListLock.unlock(); //std::cout << "entitylist unlocked!\n";
	return 0;
}

void World::RemoveEntity(int id)
{

}

int World::AddCreature(int id, Creature *creature)
{
	creatureListLock.lock(); //std::cout << "playerlist locked!\n";
	auto it = creatureList.find(id);
	if(it == creatureList.end())
	{
		creatureList.insert(std::pair<short, Creature*>(id, creature));
		CLIENT(
			eventHandler.AddEventCallback(creature, [creature] (App& a, const sf::Event& e, GameUtility* gUtil) { creature->EventUpdate(a, e, gUtil); });
		)
	}
	else
		std::cout << "Attempt to add player that already exists! " << id << std::endl;

	creatureListLock.unlock(); //std::cout << "playerlist unlocked!\n";
	return 0;
}

void World::RemoveCreature(int id)
{
	creatureListLock.lock(); //std::cout << "playerlist locked!\n";
	auto it = creatureList.find(id);
	if(it != creatureList.end())
	{
		CLIENT(
			eventHandler.RemoveEventCallback(creatureList[id]);
		)
			delete(it->second);
		creatureList.erase(id);
	}
	else
		std::cout << "Attempt to remove player that doesn't exist! " << id << std::endl;
	creatureListLock.unlock(); //std::cout << "playerlist unlocked!\n";
}

Creature* World::getCreature(int id)
{
	//creatureListLock.lock(); //std::cout << "playerlist locked!\n";
	auto it = creatureList.find(id);
	//creatureListLock.unlock(); //std::cout << "playerlist unlocked!\n";
	return (it == creatureList.end()) ? nullptr : it->second;
}

void World::SetCreature(int id, Creature *creature)
{
	creatureListLock.lock(); //std::cout << "playerlist locked!\n";
	delete(creatureList.find(id)->second);
	creatureList.erase(id);
	creatureList.insert(std::pair<short, Creature*>(id, creature));
	creatureListLock.unlock(); //std::cout << "playerlist unlocked!\n";
}

bool World::isBlockSolid(long x,long y)
{
	Block *block = getBlock(x, y, 2);
	if (block != nullptr)
	{
		return block->isSolid();
	}
	return false;
}

Chunk *World::getChunk(long x, long y)
{
	x += chunkMatrix.second;

	if (x >= 0)
	{
		if (isColumnInsideChunkMatrix(x))
		{
			auto it = chunkMatrix.first.at(x);
			y += it.second;

			if (y>= 0)
			{
				if (isChunkInsideChunkColumn(y, it.first))
				{
					if (it.first.at(y) != nullptr)
					{
						return it.first.at(y);
					}
				}
			}
		}
	}
	return nullptr;
}

Chunk *World::getGenerateChunk(long x, long y, GameUtility *gameUtility)
{
	Expand(x, y, nullptr);

	int xx = x + chunkMatrix.second;

	auto &it = chunkMatrix.first.at(xx);
	int yy = y + it.second;

	if (it.first.at(yy) == nullptr)
	{
		return it.first.at(yy) = generator(x, y, gameUtility);//(x, y, this);
	}
	return it.first.at(yy);

}