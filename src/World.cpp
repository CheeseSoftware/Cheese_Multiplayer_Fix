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
	for (int x = 0; x < 3; x++)
	{ 
		chunkMatrix.first.push_back(ChunkColumnType(std::deque<Chunk*>(),0));
		for (int y = 0; y < 3; y++)
		{
			Chunk* chunk = new Chunk();
			chunk->setBlock(2, 1, 1, new  BlockSolid(1));
			chunkMatrix.first[x].first.push_back(chunk);
		}
	}

#ifdef _SERVER
	for(int i = -256; i < 256; i++)
	{
		setBlockAndMetadataClientOnly(i, 64, 2, 1, 3, gameUtility);
		setBlockAndMetadataClientOnly(i, -64, 2, 1, 3, gameUtility);
		setBlockAndMetadataClientOnly(64, i, 2, 1, 3, gameUtility);
		setBlockAndMetadataClientOnly(-64, i, 2, 1, 3, gameUtility);
	}
#endif
}

#ifndef _SERVER
void World::EventUpdate(App &app, const sf::Event &event, GameUtility *gameUtility)
{
	eventHandler.EventUpdate(app, event, gameUtility);
}

void World::Draw(App &app, GameUtility *gameUtility) // >.<
{
	chunkMatrixLock.lock();
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

	chunkMatrixLock.unlock();

	entityListLock.lock();
	for (Entity *entity : entityList)
	{
		entity->Draw(app, gameUtility);
	}
	entityListLock.unlock();

	playerListLock.lock();
	for(std::pair<short, Player*> pair : playerList)
	{
		pair.second->Draw(app, gameUtility);
	}
	playerListLock.unlock();
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

	for(std::pair<short, Player*> pair : playerList)
	{
#ifdef _SERVER
		pair.second->Update(app, gameUtility);
#else
		pair.second->Update(app, gameUtility);
#endif
	}
}

void World::setBlock(long x, long y, long layer, unsigned short id, GameUtility *gameUtility)
{
	setBlockAndMetadata(x, y, layer, id, 0, gameUtility);
}

void World::setBlockAndMetadata(long x, long y, long layer, unsigned short id, unsigned short metadata, GameUtility *gameUtility)
{
	MessageType messageType = setBlockAndMetadataClientOnly(x, y, layer, id, metadata, gameUtility);
	if(id != 0)
		gameUtility->SendPacket(gameUtility->getBlockRegister().getBlockType(id)->OnSend(messageType, x, y, layer, id, metadata, gameUtility));
	else
	{
		sf::Packet packet;
		packet << (sf::Int16)BlockPlace << (sf::Int32)x << (sf::Int32)y << (sf::Uint16)layer << (sf::Uint16)id << (sf::Uint16)metadata;
		gameUtility->SendPacket(packet);
	}
}

void World::setBlockMetadata(long x, long y, long layer, unsigned short metadata, GameUtility *gameUtility)
{
	if (setBlockMetadataClientOnly(x, y, layer, metadata, gameUtility))
	{
		sf::Packet packet;
		packet << (sf::Int16)BlockMetadataChange << (sf::Int32)x << (sf::Int32)y << (sf::Uint16)layer << (sf::Uint16)metadata;
		gameUtility->SendPacket(packet);
	}
}

MessageType World::setBlockAndMetadataClientOnly(long x, long y, long layer, unsigned short id, unsigned short metadata, GameUtility *gameUtility)
{
	chunkMatrixLock.lock();
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
			chunkMatrixLock.unlock();
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
					chunkMatrixLock.unlock();
					return BlockMetadataChange;
				}

				chunkMatrixLock.unlock();
				return NullMessage;
			}
		}
		else if (id == 0)
		{
			chunkMatrixLock.unlock();
			return NullMessage;
		}
	}

	c->setBlock(layer, xxx, yyy, gameUtility->getBlockRegister().getBlockType(id));
	c->setMetadata(layer, xxx, yyy, metadata);
	chunkMatrixLock.unlock();
	return BlockPlace;

	chunkMatrixLock.unlock();
	return NullMessage;
}

MessageType World::setBlockMetadataClientOnly(long x, long y, long layer, unsigned short metadata, GameUtility *gameUtility)
{
	chunkMatrixLock.lock();
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
					c->setMetadata(layer, xxx, yyy, metadata);
					chunkMatrixLock.unlock(); //std::cout << "chunkmatrix unlocked!\n";
					return BlockMetadataChange;
				}
			}
		}
	}
	chunkMatrixLock.unlock(); //std::cout << "chunkmatrix unlocked!\n";
	return NullMessage;
}

Block *World::getBlock(long x, long y, long layer)
{
	Block *block = getBlockAndMetadata(x, y, layer).first;
	return block;
}

std::pair<Block*, unsigned short> World::getBlockAndMetadata(long x, long y, long layer)
{
	//chunkMatrixLock.lock(); //std::cout << "chunkmatrix locked!\n";
	if (lastBlock.first._Equals(std::tuple<long, long, short>(x, y, layer)))
	{
		//	chunkMatrixLock.unlock(); //std::cout << "chunkmatrix unlocked!\n";
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
				//chunkMatrixLock.unlock(); //std::cout << "chunkmatrix unlocked!\n";
				return *(lastBlock = std::pair<std::tuple<long, long, unsigned short>, 
					std::pair<Block*, unsigned short>*>
					(std::tuple<long, long, unsigned short>(x, y, layer),
					&chunk->getBlockAndMetadata(xxx, yyy, layer))).second;
				//std::pair<Block*, unsigned short>(chunk->getBlock(layer, xxx, yyy), chunk->getMetadata(layer, xxx, yyy));
			}
		}
	}
	//chunkMatrixLock.unlock(); //std::cout << "chunkmatrix unlocked!\n";
	return std::pair<Block*, unsigned short>(nullptr, 0);
}

const std::pair<Block*, unsigned short> World::getPhysicBlock() const
{
	return physicBlock;
}

void World::Expand(long x, long y, Chunk* chunk)
{
	//chunkMatrixLock.lock(); //std::cout << "chunkmatrix locked!\n";
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

	//chunkMatrixLock.unlock(); //std::cout << "chunkmatrix unlocked!\n";
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

int World::AddPlayer(int id, Player *player)
{
	playerListLock.lock(); //std::cout << "playerlist locked!\n";
	auto it = playerList.find(id);
	if(it == playerList.end())
	{
		playerList.insert(std::pair<short, Player*>(id, player));
		CLIENT(
			eventHandler.AddEventCallback(player,[player] (App& a, const sf::Event& e, GameUtility* gUtil) { player->EventUpdate(a, e, gUtil); });
		)
	}
	else
		std::cout << "Attempt to add player that already exists! " << id << std::endl;

	playerListLock.unlock(); //std::cout << "playerlist unlocked!\n";
	return 0;
}

void World::RemovePlayer(int id)
{
	playerListLock.lock(); //std::cout << "playerlist locked!\n";
	auto it = playerList.find(id);
	if(it != playerList.end())
	{
		CLIENT(
			//eventHandler.RemoveEventCallback(playerList[id]);
			)
			delete(it->second);
		playerList.erase(id);
	}
	else
		std::cout << "Attempt to remove player that doesn't exist! " << id << std::endl;
	playerListLock.unlock(); //std::cout << "playerlist unlocked!\n";
}

Player* World::GetPlayer(int id)
{
	//playerListLock.lock(); //std::cout << "playerlist locked!\n";
	auto it = playerList.find(id);
	//playerListLock.unlock(); //std::cout << "playerlist unlocked!\n";
	return (it == playerList.end()) ? nullptr : it->second;
}

void World::SetPlayer(int id, Player *player)
{
	playerListLock.lock(); //std::cout << "playerlist locked!\n";
	delete(playerList.find(id)->second);
	playerList.erase(id);
	playerList.insert(std::pair<short, Player*>(id, player));
	playerListLock.unlock(); //std::cout << "playerlist unlocked!\n";
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
