#ifdef _SERVER
#include <iostream>
#include <string>
#include <SFML\Network.hpp>
#include "ServerState.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "World.h"
#include "BlockSolid.h"
#include "BlockBackground.h"
#include "App.h"
#include "Packet.h"
#include <SFML\Graphics.hpp>



ServerState::ServerState(App &app) : GameUtility(app)
{
	sC = new ServerConnection(5001, currentWorld);
}

ServerState::~ServerState()
{
	delete currentWorld;
}

GameState *ServerState::Update(App &app)
{
	//std::cout << "updates per second: " << 1/APP(app).getFrameTime() << std::endl;
	while (!packetDataList->empty())
	{
		sC->Broadcast(packetDataList->front());
		packetDataList->pop();
	}
	sC->Run();
	ProcessPackets(this);
	return this;
}

void ServerState::ProcessPackets(GameUtility *gameUtility)
{
	auto packets = sC->packets;
	sC->packets = std::queue<std::pair<sf::Packet*, Client*>>();

	while(packets.size() > 0)
	{
		auto data = packets.front();
		sf::Packet* packet = data.first;
		Client *client = data.second;

		sf::Uint16 packetType;
		if(!(*packet >> packetType))
			std::cout << "fishexception at serverstate where there is a variable called packetType but only the first instance!";
		//throw("ERROR: Server could not extract data");
		//std::cout << "packettype " << packetType << std::endl;

		sf::Packet* const originalPacket = new sf::Packet(*packet);

		switch(packetType)
		{
		case RequestInit:
			{
				Player *joined = new Player(0, 0, 16, 16, false, "smileys.png", 0, "temp");
				currentWorld->AddPlayer(client->ID, joined);
				sf::Packet send;
				send << (sf::Uint16) Init << (sf::Uint16)client->ID;
				for(std::pair<int, Client*> pair : sC->clients)
				{
					Player* temp = currentWorld->GetPlayer(pair.first);
					if(temp != nullptr)
						send << (sf::Int16)pair.first << (float)temp->getPosition().x << (float)temp->getPosition().y << (sf::Int16)temp->getSize().x << (sf::Int16)temp->getSize().y;
				}
				client->socket->send(send);
			}
			break;
		case Ping: //Get client ping
			{
				sf::Time ping = client->pingClock.getElapsedTime();
				float totalPing = ping.asMilliseconds();
				client->ping = totalPing;
				client->isMeasuringPing = false;
			}
			break;
		case Kick: //Server has kicked client (Client receiver only)
			{
			}
			break;
		case PlayerJoin: //A player has joined or left the server
			{
				sf::Uint16 clientId = client->ID;
				std::cout << "client joined blabla " << clientId << std::endl;
				float xPos;
				float yPos;
				sf::Packet send;
				if(!(*packet >> xPos >> yPos))
					std::cout << "ERROR: Server could not extract data: PlayerJoin" << std::endl;
				currentWorld->AddPlayer(client->ID, new Player(xPos, yPos, 16, 16, true, "smileys.png", 0, "temp"));
				send << packetType << clientId << xPos << yPos;
				sC->Broadcast(send);
				break;
			}
		case PlayerLeft:
			{
				sf::Packet send;
				currentWorld->RemovePlayer(client->ID);
				send.clear();
				send << (sf::Uint16)PlayerLeft << (sf::Uint16)client->ID;
				sC->Broadcast(send);
			}
			break;
		case PlayerMove:
			{
				float xPos;
				float yPos;
				float speedX;
				float speedY;
				float angle;
				float horizontal;
				float vertical;
				*packet >> xPos >> yPos >> speedX >> speedY >> angle >> horizontal >> vertical;
				Player* p = currentWorld->GetPlayer(client->ID);
				if (p != nullptr)
				{
					sf::Packet packet;
					sf::Int16 clientid = client->ID;
					if(!(packet << (sf::Uint16)PlayerMove << clientid << xPos << yPos << speedX << speedY << angle << horizontal << vertical))
						std::cout << "ERROR: Server could not extract data: PlayerMove" << std::endl;
					sC->Broadcast(packet);
					p->CreatureMove(xPos, yPos, speedX, speedY, angle, horizontal, vertical);
				}
			}
			break;
		case BlockPlace:
			{
				sf::Int32 xPos;
				sf::Int32 yPos;
				sf::Uint16 layer;
				sf::Uint16 id;
				sf::Uint16 metadata;
				if(!(*packet >> xPos >> yPos >> layer >> id >> metadata))
					std::cout << "ERROR: Server could not extract data: BlockPlace" << std::endl;
				if(id != 0)
					Block* temp = blockRegister->getBlockType(id)->OnReceive(originalPacket, gameUtility);
				else
					gameUtility->getCurrentWorld()->setBlockAndMetadata(xPos, yPos, layer, 0, metadata, gameUtility);
			}
			break;
		case BlockMetadataChange:
			{
				sf::Int32 xPos;
				sf::Int32 yPos;
				sf::Uint16 layer;
				sf::Uint16 metadata;
				if(!(*packet >> xPos >> yPos >> layer >> metadata))
					std::cout << "ERROR: Server could not extract data: BlockMetadataChange" << std::endl;
				currentWorld->setBlockMetadata(xPos, yPos, layer, metadata, this);
			}
			break;
		}
		delete packet;
		delete originalPacket;
		packets.pop();
	}
}
#endif