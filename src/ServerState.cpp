#ifdef _SERVER
#include <iostream>
#include <string>
#include <SFML\Network.hpp>
#include "ServerState.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "World.h"
#include "Chunk.h"
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
	//std::cout << "updates per second: " << 1/(app).getFrameTime() << std::endl;
	while (!packetDataList->empty())
	{
		std::cout << "packets " << packetDataList->size() << std::endl;
		sC->Broadcast(packetDataList->front());
		packetDataList->pop();
	}
	currentWorld->Update(app, this);
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
			std::cout << "ERROR: Server could not extract packet type";
		//throw("ERROR: Server could not extract data");
		//std::cout << "packettype " << packetType << std::endl;

		sf::Packet* const originalPacket = new sf::Packet(*packet);

		switch(packetType)
		{
		case RequestInit:
			{
				//std::cout << "Received RequestInit" << std::endl;
				Player *joined = new Player(client->ID, 0, 0, 16, 16, false, "smileys.png", 0, "temp");
				sf::Packet send;
				send << (sf::Uint16) Init << (sf::Uint16)client->ID;
				for(std::pair<int, Client*> pair : sC->clients)
				{
					Creature* temp = currentWorld->getCreature(pair.first);
					if(temp != nullptr)
						send << (sf::Int16)pair.first << (float)temp->getPosition().x << (float)temp->getPosition().y << (sf::Int16)temp->getSize().x << (sf::Int16)temp->getSize().y;
				}
				currentWorld->AddCreature(client->ID, joined);
				client->socket->send(send);

				send.clear();
				send << (sf::Uint16)PlayerJoin << (sf::Uint16)client->ID << joined->getX() << joined->getY();
				sC->Broadcast(send);
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
		case Kicked: //Server has kicked client (Client receiver only)
			{
			}
			break;
		case Chat:
			{
				sf::Uint16 id;
				char *message;
				if(!(*packet >> id >> message))
					std::cout << "ERROR: Server could not extract data: Chat" << std::endl;
				//if(!message.contains(shit))
				sf::Packet toSend;
				toSend << id << message;
				sC->Broadcast(toSend);
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
				currentWorld->AddCreature(client->ID, new Player(clientId, xPos, yPos, 16, 16, true, "smileys.png", 0, "temp"));
				send << packetType << clientId << xPos << yPos;
				sC->Broadcast(send);
				break;
			}
		case PlayerLeft:
			{
				sf::Packet send;
				currentWorld->RemoveCreature(client->ID);
				send.clear();
				send << (sf::Uint16)PlayerLeft << (sf::Uint16)client->ID;
				sC->Broadcast(send);
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
					// usch, såhär kan du inte göra!
					//player->setPosition(x, y);
					player->setHealth(100);
				}
				sf::Packet toSend;
				toSend << (sf::Uint16)PlayerRespawn << id << x << y;
				sC->Broadcast(toSend);
			}
			break;
		case CreatureMove:
			{
				float xPos;
				float yPos;
				float speedX;
				float speedY;
				float angle;
				float horizontal;
				float vertical;
				*packet >> xPos >> yPos >> speedX >> speedY >> angle >> horizontal >> vertical;
				Creature* p = currentWorld->getCreature(client->ID);
				if (p != nullptr)
				{
					sf::Packet packet;
					sf::Int16 clientid = client->ID;
					if(!(packet << (sf::Uint16)CreatureMove << clientid << xPos << yPos << speedX << speedY << angle << horizontal << vertical))
						std::cout << "ERROR: Server could not extract data: PlayerMove" << std::endl;
					sC->Broadcast(packet);
					p->CreatureMove(xPos, yPos, speedX, speedY, angle, horizontal, vertical);
				}
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
					gameUtility->getCurrentWorld()->setBlockAndMetadata(xPos, yPos, layer, 0, metadata, gameUtility);
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
					std::cout << "ERROR: Server could not extract data: BlockMetadataChange" << std::endl;
				currentWorld->setBlockMetadata(xPos, yPos, layer, metadata, this);
			}
			break;
		case RequestChunks:
			{
				sf::Packet sendChunksPacket = sf::Packet();
				sendChunksPacket << (sf::Uint16) Chunks;
				while(!packet->endOfPacket())
				{
					sf::Int32 currentChunkX;
					sf::Int32 currentChunkY;
					if(!(*packet >> currentChunkX >> currentChunkY))
					{
						std::cout << "ERROR: Server could not extract data: RequestChunks" << std::endl;
						break;
					}
					Chunk *chunk = currentWorld->getGenerateChunk(currentChunkX, currentChunkY, gameUtility);
					if(chunk != nullptr)
					{
						for(int x = 0; x < 16; x++)
						{
							for(int y = 0;  y < 16; y++)
							{
								for(int layer = 0; layer < 6; layer++)
								{
									std::pair<Block*, unsigned short> pair = chunk->getBlockAndMetadata(x, y, layer);
									if(pair.first != nullptr)
									{
										long currentBlockX = currentChunkX * 16 + x - 16;
										long currentBlockY = currentChunkY * 16 + y - 16;
										sf::Uint16 blockId = blockRegister->getBlockIdByTypeId(typeid(*pair.first).hash_code());
										if(blockId != 0)
										{
											sf::Uint16 blockMetadata = pair.second;
											pair.first->OnSend(&sendChunksPacket, BlockPlace, currentBlockX, currentBlockY, layer, blockId, blockMetadata, gameUtility);
											//sendChunksPacket << blockId << blockMetadata << (sf::Int32)currentBlockX << (sf::Int32)currentBlockY << (sf::Uint16)layer;
										}
									}
								}
							}
						}
					}
				}
				client->socket->send(sendChunksPacket);
			}
			break;
		}
		delete packet;
		delete originalPacket;
		packets.pop();
	}
}
#endif