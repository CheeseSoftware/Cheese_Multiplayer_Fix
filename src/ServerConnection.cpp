#include "ServerConnection.h"
#include "Player.h"
#include "Client.h"
#include "World.h"

ServerConnection::ServerConnection(int port, World *world)
{
	currentWorld = world;
	acceptReceiveThread = new sf::Thread(&ServerConnection::AcceptReceive, this);
	if(s.listen(port) != sf::Socket::Status::Done)
		std::cout << "Failed to bind to port " << port << ", maybe already a server listening on this port?" << std::endl;
	else
		std::cout << "Server listening to port " << port << std::endl;
	pingTimeout.restart();
	s.setBlocking(true);
	selector.add(s);
	acceptReceiveThread->launch();
}


ServerConnection::~ServerConnection(void)
{
}

void ServerConnection::Update(void)
{
	float ElapsedTime = pingTimeout.getElapsedTime().asMilliseconds();
	if(ElapsedTime > 1000)
	{
		pingTimeout.restart();
		PingClients();
	}
}

void ServerConnection::PingClients(void)
{
	for (auto pair : clients)
	{
		Client *client = pair.second;
		if(!client->isMeasuringPing)
		{
			std::cout << "Client " << client->ID << " has ping " << client->ping << std::endl;
			sf::Packet send;
			sf::Uint16 ping = Ping;
			send << ping;
			client->socket->send(send);
			client->ping = 0;
			client->pingClock.restart();
			client->isMeasuringPing = true;
		}
		else
		{
			float currentPing = client->pingClock.getElapsedTime().asMilliseconds();
			std::cout << "Client " << client->ID << " has ping " << currentPing << std::endl;
			if(currentPing > 1000)
			{
				if(client->socket->getRemoteAddress() == sf::IpAddress::None)
				{
					lockObject.lock();
					toKick.emplace(std::pair<int, std::string>(client->ID, "Too high ping"));
					lockObject.unlock();
				}
				else
				{
					sf::Packet send;
					sf::Uint16 ping = Ping;
					send << ping;
					client->socket->send(send);
					client->ping = 0;
					client->pingClock.restart();
					client->isMeasuringPing = true;
				}
			}
		}
	}
}

int ServerConnection::GetFreeClientId()
{
	for(int i = 0;; i++)
	{
		if(clients.find(i) == clients.end())
		{
			std::cout << "Returned client id " << i << std::endl;
			return i;
		}
	}
}

void ServerConnection::AcceptReceive()
{
	while(true)
	{
		if (selector.wait())
		{
			if(selector.isReady(s))
			{
				Client *client = new Client();
				if (s.accept(*client->socket) == sf::Socket::Done)
				{
					int freeClientId = GetFreeClientId();
					if(freeClientId != -1)
					{
						client->pingClock = sf::Clock();
						client->socket->setBlocking(true);
						client->ID = freeClientId;
						lockObject.lock();
						clients.insert(std::pair<int, Client*>(freeClientId, client));
						lockObject.unlock();
						selector.add(*client->socket);
						std::cout << client->socket->getRemoteAddress() << " connected on socket " << freeClientId << std::endl;
					}
				}
				else
				{
					std::cout << "Failed to accept connecting socket!" << std::endl;
					delete client;
				}
			}
			else
			{
				lockObject.lock();
				for(std::pair<int, Client*> pair : clients)
				{
					if (selector.isReady(*pair.second->socket))
					{
						Client *client = pair.second;
						if(client->socket->getRemoteAddress() !=sf::IpAddress::None)
						{
							sf::Packet *received = new sf::Packet();
							sf::Socket::Status status = client->socket->receive(*received);
							if (status == sf::Socket::Done)
							{
								if(received != nullptr && client != nullptr && received->getDataSize() > 0)
								{
									lockObject.lock();
									packets.push(std::pair<sf::Packet*, Client*>(received, client));
									lockObject.unlock();
								}
							}
							else if(status == sf::Socket::Disconnected)
							{
								lockObject.lock();
								toKick.emplace(pair.first, "Socket disconnected");
								lockObject.unlock();
								delete received;
							}
						}
						else
							std::cout << "Failed to receive from sending socket!" << std::endl;
					}
				}
				lockObject.unlock();
			}
		}
	}
}

void ServerConnection::KickClient(int ID, std::string reason)
{
	lockObject.lock();
	auto client = clients.find(ID);
	if(client != clients.end())
	{
		//Send a kick message
		const char *kickmsg = reason.c_str();
		sf::Packet send;
		send << (sf::Uint16)Kicked << kickmsg;
		client->second->socket->send(send);

		//Kick the client
		selector.remove(*client->second->socket);
		delete clients.at(ID);
		if(!clients.erase(ID))
			std::cout << "Could not remove client! KickClient" << std::endl;
		currentWorld->RemoveCreature(ID);
		std::cout << "Kicked client: " << ID << " Reason: " << reason << std::endl;

		//Tell other clients that the client has left
		send.clear();
		send << (sf::Uint16) PlayerLeft << (sf::Uint16)ID;
		Broadcast(send);
	}
	lockObject.unlock();
}

void ServerConnection::Broadcast(sf::Packet packet)
{
	for(std::pair<int, Client*> pair : clients)
	{
		pair.second->socket->send(packet);
	}
}
