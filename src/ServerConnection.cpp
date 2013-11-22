#include "ServerConnection.h"
#include "Player.h"

ServerConnection::ServerConnection(int port, World *world)
{
	currentWorld = world;
	sf::Thread *acceptReceiveThread = new sf::Thread(&ServerConnection::AcceptReceive, this);
	if(s.listen(port) != sf::Socket::Status::Done)
	{
		std::cout << "Failed to bind to port " << port << ", maybe already a server listening on this port?" << std::endl;
		std::cin.get();
	}
	else
	{
		pingTimeout.restart();
		s.setBlocking(true);
		selector.add(s);
		acceptReceiveThread->launch();
		std::cout << "Server listening to port " << port << std::endl;
	}
}


ServerConnection::~ServerConnection(void)
{
}

void ServerConnection::Run(void)
{
	float ElapsedTime = pingTimeout.getElapsedTime().asMilliseconds();
	if(ElapsedTime > 1000)
	{
		pingTimeout.restart();
		//PingClients();
	}
}

void ServerConnection::PingClients(void)
{
	std::vector<int> *toKick = new std::vector<int>();
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
			client->pingClock.restart();
			client->isMeasuringPing = true;
		}
		else if(client->socket->getRemoteAddress() != sf::IpAddress::None)
		{
			float currentPing = client->pingClock.getElapsedTime().asMilliseconds();
			if(currentPing > 5000)
			{
				//Kick client, too high ping
				std::cout << "Client " << client->ID << " has ping " << client->ping << std::endl;
				toKick->push_back(client->ID);
			}
		}
	}

	for(int i : *toKick)
	{
		KickClient(i, "Too high ping");
	}
	toKick->clear();
	delete toKick;
}

int ServerConnection::GetFreeClientId()
{
	for(int i = 0; i < 1024; i++)							//Magic number, fix!
	{
		if(clients.find(i) == clients.end())
		{
			//Found a free client id
			std::cout << "Returned client id " << i << std::endl;
			return i;
		}
	}
}

void ServerConnection::AcceptReceive()
{
	std::vector<int> *toKick = new std::vector<int>();
	while(true)
	{
		if (selector.wait(sf::seconds(2)))
		{
			if(selector.isReady(s))
			{
				//Client is connecting
				//std::cout << "Client is connecting.." << std::endl;
				Client *client = new Client();
				if (s.accept(*client->socket) == sf::Socket::Done)
				{
					int freeClientId = GetFreeClientId();
					if(freeClientId != -1)
					{
						//Accept the client
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
				//Check if any client has sent data
				lockObject.lock();
				for(std::pair<int, Client*> pair : clients)
				{
					if (selector.isReady(*pair.second->socket))
					{
						//std::cout << "Client is ready for receive.." << std::endl;
						Client *client = pair.second;
						if(client->socket->getRemoteAddress() !=sf::IpAddress::None)
						{
							sf::Packet *received = new sf::Packet();
							sf::Socket::Status status = client->socket->receive(*received);
							if (status == sf::Socket::Done)
							{
								packets.push(std::pair<sf::Packet*, Client*>(received, client));
							}
							else if(status == sf::Socket::Disconnected)
							{
								//std::cout << "Client disconnected while receiving!" << std::endl;
								toKick->push_back(pair.first);
								delete received;
							}
						}
						else
							std::cout << "Failed to receive from sending socket!" << std::endl;
					}
				}
				lockObject.unlock();
				for(int i : *toKick)
					KickClient(i, "Disconnected");
				toKick->clear();
			}
		}
	}
	delete toKick;
}

void ServerConnection::KickClient(int ID, std::string reason)
{
	lockObject.lock();
	auto client = clients.find(ID);
	if(client != clients.end())
	{
		//Tell the client a kick message
		const char *kickmsg = reason.c_str();
		sf::IpAddress ip = client->second->socket->getRemoteAddress();
		sf::Packet send;
		send << (sf::Uint16)Kicked << kickmsg;
		client->second->socket->send(send);

		//Kick the client
		selector.remove(*client->second->socket);
		delete clients.at(ID);
		if(!clients.erase(ID))
			std::cout << "Could not remove client! KickClient" << std::endl;
		currentWorld->RemovePlayer(ID);
		std::cout << "Kicked client: " << ID << " Reason: " << reason << std::endl;

		//Tell other clients that client has left
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
