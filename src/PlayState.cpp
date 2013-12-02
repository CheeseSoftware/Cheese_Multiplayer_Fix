#ifndef _SERVER

#include <iostream>
#include <sstream>
#include <string>
#include <SFML\Network.hpp>
#include "GameState.h"
#include "PlayState.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "World.h"
#include "Camera.h"
#include "Player.h"
#include "BlockSolid.h"
#include "BlockBackground.h"
#include "EventHandler.h"
#include "TextureContainer.h"
#include "connection.h"
#include "noobishBlockMenu.h"
#include "BlockRegister.h"
#include "Button.h"
#include "TextBox.h"
#include "Minimap.h"

namespace sf
{
	class RenderWindow;
}

extern int _argc;
extern char** _argv;

PlayState::PlayState(App &app)
	: GameUtility(app)
	, hudView(sf::FloatRect(0.f, 0.f, (float)app.getSize().x, (float)app.getSize().y))
{
	minimap = new gui::Minimap(0, 0, 200, 200);
	fpsClock.restart();

	char* str_ip = "127.0.0.1";

	if (_argc >= 2)
	{
		str_ip = _argv[1];
	}
	std::cout << "Connecting to " << str_ip << " ...\n";

	sf::IpAddress ip(str_ip);//std::string ip;
	int port;

	noobishBlockMenu = new NoobishBlockMenu(currentWorld, this);//InGameUI(app, tC, *currentWorld);
	connection = new Connection(5001, ip);
	blockRegister->RegisterBlockTextures(*tC);



	hud = new gui::MenuItemContainer(0, 0, 0, 0);
	hud->setPositionType(TopLeft);
	font = new sf::Font();
	if (!font->loadFromFile("font.ttf"))
		throw "font.ttf not found";
	std::stringstream ss;
	ss << "Member of first" << std::endl;
	pos = new gui::Label(50, 50, 200, 50, new sf::String(ss.str()), font, 10, 10);
	//pos->setTexture(&getTextureContainer().getTextures("Test.png")[0]);
	hud->Add(pos);
	/*for(int i = 0; i < 200; i += 50)
	{
	std::stringstream ss;
	ss << "Member of first" << std::endl;
	gui::Label *pos = new gui::Label(50, i, 200, 50, new sf::String(ss.str()), font, 10, 10);
	pos->setTexture(&getTextureContainer().getTextures("Test.png")[0]);
	hud->Add(pos);
	}*/
	/*gui::MenuItemContainer *second = new gui::MenuItemContainer(100, 200, app.getSize().x, app.getSize().y);
	hud->Add(second);
	for(int i = 0; i < 200; i += 50)
	{
	std::stringstream ss;
	ss << "Button of second" << std::endl;
	/*auto leftClick = [] (App& app, const sf::Event& event, GameState* gameState, float x, float y) -> GameState*
	{
	std::cout << "a button was leftclicked!" << std::endl;
	return nullptr;
	};
	auto rightClick = [] (App& app, const sf::Event& event, GameState* gameState, float x, float y) -> GameState*
	{
	std::cout << "a button was rightclicked!" << std::endl;
	return nullptr;
	};*/
	/*gui::TextBox *pos = new gui::TextBox(50, i, 200, 50, new sf::String(ss.str()), font, 500, 500);
	//gui::Button *pos = new gui::Button(50, i, 200, 50, new sf::String(ss.str()), font, leftClick, rightClick);
	second->Add(pos);
	}*/
}

PlayState::~PlayState()
{

}






void PlayState::EventUpdate(App &app, const sf::Event &event)
{
	if (event.type == sf::Event::Resized)
	{
		reinterpret_cast<sf::View*>(camera)->setSize(sf::Vector2f(//->setViewport(sf::FloatRect(0.f, 0.f,
			app.getSize().x,
			app.getSize().y));

		hudView.setSize(app.getSize().x, app.getSize().y);
		hudView.setCenter(sf::Vector2f(app.getSize().x/2, app.getSize().y/2));
	}

	hud->EventUpdate(app, event, this, hud->getPosition().x, hud->getPosition().y);
	currentWorld->EventUpdate(app, event, this);
	noobishBlockMenu->EventUpdate(app, event, this);
}

GameState *PlayState::Update(App &app)
{
	if (fpsClock.getElapsedTime().asMilliseconds() > 25)
	{
		//if (1/app.getFrameTime() < 90)
		//std::cout << "fps: " << 1/app.getFrameTime() << " << LOW FPS!!!!!! <<<<<<\n";
		//else
		//std::cout << "fps: " << 1/app.getFrameTime() << "\n";
		fpsClock.restart();
	}
	//else if (1/app.getFrameTime() < 50.f)
	/*{
	std::cout << "fps: " << 1/app.getFrameTime() << " LOW FPS!\n";
	fpsClock.restart();
	}*/

	hud->Update(app);
	currentWorld->Update(app, this);
	camera->Update(app);
	minimap->Update(app, this);


	while (!packetDataList->empty())
	{
		sf::Packet *temp = new sf::Packet(packetDataList->front());
		sf::Uint16 id;
		*temp >> id;
		std::cout << "sending packet " << id << std::endl;
		connection->client->socket->send(packetDataList->front());
		packetDataList->pop();
	}

	connection->Run();
	ProcessPackets(this);
	return this;
} 

void PlayState::Draw(App &app)
{
	app.setView(*reinterpret_cast<sf::View*>(camera));
	currentWorld->Draw(app, this);
	app.setView(hudView);
	if(getCamera().getEntity() != nullptr)
	{
		std::stringstream temp;
		temp << "HP: " << ((Player*)getCamera().getEntity())->getHealth() << std::endl;
		delete pos->getText();
		pos->setText(new sf::Text(sf::String(temp.str()), *font));
	}
	hud->Draw(app, 0, 0, app.getSize().x, app.getSize().y);
	noobishBlockMenu->Draw(app, this); // < orsakar lagg temp
	minimap->Draw(app, 0, 0, 400, 400);
}

void PlayState::ProcessPackets(GameUtility *gameUtility)
{
	connection->globalMutex.lock();
	std::queue<sf::Packet*> packets = connection->packets;
	connection->packets = std::queue<sf::Packet*>();
	connection->globalMutex.unlock();

	while(packets.size() > 0)
	{
		sf::Packet* packet = packets.front();
		//Now process packets
		sf::Uint16 packetType;
		sf::Uint16 wtf;
		if(!(*packet >> packetType))
			std::cout << "ERROR: Client could not extract data: Packet type " << !packet->endOfPacket() << std::endl;
		//std::cout << "Client got packet " << packetType << " wtf?: " << wtf << std::endl;

		sf::Packet* const originalPacket = new sf::Packet(*packet);

		switch(packetType)
		{
		case Init:
			{
				std::cout << "init" << std::endl;
				sf::Int16 myId;
				if(!(*packet >> myId))
					std::cout << "ERROR: Client could not extract data: Init, myId" << std::endl;
				connection->client->ID = myId;
				Player *me = new Player(myId, 0, -1024, 16, 16, true, "smileys.png", 0, "temp");
				currentWorld->AddCreature(myId, me);
				while(!packet->endOfPacket())
				{
					sf::Int16 clientId;
					float xPos;
					float yPos;
					sf::Int16 sizeX;
					sf::Int16 sizeY;

					if(!(*packet >> clientId  >> xPos >> yPos >> sizeX >> sizeY))
						std::cout << "ERROR: Client could not extract data: Init" << std::endl;
					else
					{
						Player *player = new Player(clientId, xPos, yPos, 16, 16, false, "smileys.png", 0, "temp");
						std::cout << "added client " << clientId << std::endl;
						currentWorld->AddCreature(clientId, player);
					}
				}
			}
			break;
		case Ping: //measure ping between sent 1 and received 1 (type)
			{
				sf::Packet packet;
				packet << (sf::Uint16)Ping;
				connection->client->socket->send(packet);
			}
			break;
		case Chat:
			{
				sf::Uint16 id;
				char *message;
				if(!(*packet >> id >> message))
					std::cout << "ERROR: Client could not extract data: Chat" << std::endl;
				//chat.write(clients[id].name << ": " << message);
			}
			break;
		case Kicked: //server kicks client (type, string message)
			{
				char *kickmsg;
				*packet >> kickmsg;
				std::cout << "Kicked by server." << std::endl;
				std::cout << "Reason: " << kickmsg << std::endl;
				std::cin.get();
			}
			break;
		case PlayerJoin:
			{
				sf::Uint16 clientId;
				float xPos;
				float yPos;
				if(!(*packet >> clientId >> xPos >> yPos))
					std::cout << "ERROR: Client could not extract data: PlayerJoin" << std::endl;
				Player* player = new Player(clientId, xPos, yPos, 16, 16, false, "smileys.png", 0, "temp");
				currentWorld->AddCreature(clientId, player);
			}
			break;
		case PlayerLeft:
			{
				sf::Uint16 clientId;
				if(!(*packet >> clientId))
					std::cout << "ERROR: Client could not extract data: PlayerLeft" << std::endl;
				currentWorld->RemoveCreature(clientId);
				std::cout << "Client " << clientId << " has left" << std::endl;
			}
			break;
		case PlayerRespawn:
			{
				sf::Uint16 id;
				sf::Int32 x;
				sf::Int32 y;
				if(!(*packet >> id >> x >> y))
					std::cout << "ERROR: Client could not extract data: PlayerRespawn" << std::endl;
				if(currentWorld->getCreature(id) == nullptr)
				{
					Player *player = new Player(id, x, y, 16, 16, false, "smileys.png", 0, "temp");
					currentWorld->AddCreature(id, player);
				}
				else
				{
					Player *player = (Player*)currentWorld->getCreature(id);
					player->setPosition(x, y);
					player->setHealth(100);
				}
			}
			break;
		case CreatureMove:
			{
				sf::Int16 ID;
				float xPos;
				float yPos;
				float speedX;
				float speedY;
				float angle;
				float horizontal;
				float vertical;
				if(!(*packet >> ID  >> xPos >> yPos >> speedX >> speedY >> angle >> horizontal >> vertical))
					std::cout << "ERROR: Client could not extract data: CreatureMove" << std::endl;
				Creature* p = currentWorld->getCreature(ID);
				if (p != nullptr && ID != connection->client->ID)
				{
					p->CreatureMove(xPos, yPos, speedX, speedY, angle, horizontal, vertical);
				}
			}
			break;
		case CreatureDamage:
			{
				sf::Uint16 id;
				float damage;
				if(!(*packet >> id >> damage))
					std::cout << "ERROR: Client could not extract data: CreatureDamage" << std::endl;
				Creature *creature = currentWorld->getCreature(id);
				if(creature != nullptr)
					creature->OnDamage(damage);
			}
			break;
		case BlockPlace:
			{
				sf::Uint16 id;
				if(!(*packet >> id))
					std::cout << "ERROR: Server could not extract data: BlockPlace: id" << std::endl;
				if(id != 0)
					blockRegister->getBlockType(id)->OnReceive(packet, id, gameUtility);
				else
				{
					sf::Int32 xPos;
					sf::Int32 yPos;
					sf::Uint16 layer;
					sf::Uint16 metadata;
					if(!(*packet >> xPos >> yPos >> layer >> metadata))
						std::cout << "ERROR: Server could not extract data: BlockPlace" << std::endl;
					gameUtility->getCurrentWorld()->setBlockAndMetadataLocal(xPos, yPos, layer, 0, metadata, gameUtility);
				}
			}
			break;
		case BlockMetadataChange:
			{
				sf::Int32 xPos;
				sf::Int32 yPos;
				sf::Uint16 layer;
				sf::Uint16 metadata;
				if(!(*packet >> xPos >> yPos >> layer >> metadata))
					std::cout << "ERROR: Client could not extract data: BlockMetadataChange" << std::endl;
				currentWorld->setBlockMetadataLocal(xPos, yPos, layer, metadata, this);
			}
			break;
		case Chunks:
			{
				while(!packet->endOfPacket())
				{
					//std::cout << "packet size left: " << packet->getDataSize() << std::endl;
					sf::Uint16 blockId;
					if(!(*packet >> blockId))
						std::cout << "ERROR: Client could not extract data: Chunks: blockId" << std::endl;
					Block *tempBlock = blockRegister->getBlockType(blockId);
					/*if(tempBlock->isUnique())
					{
					Block* newBlock = static_cast<Block*>(malloc(sizeof(*tempBlock)));
					*newBlock = *tempBlock;
					newBlock->OnReceive(packet, blockId, gameUtility);
					}*/
					tempBlock->OnReceive(packet, blockId, gameUtility);
				}
			}
			break;
		}
		delete packet;
		delete originalPacket;
		packets.pop();
	}
}
#endif