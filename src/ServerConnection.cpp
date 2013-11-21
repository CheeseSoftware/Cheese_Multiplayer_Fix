#include "ServerConnection.h"

ServerConnection::ServerConnection(int port, World *world)
{
	currentWorld = world;
	//maxClients = 1024;
	s.setBlocking(true);
	selector = sf::SocketSelector();
	sf::Thread *acceptThread = new sf::Thread(&ServerConnection::Accept, this);
	sf::Thread *receiveThread = new sf::Thread(&ServerConnection::Receive, this);
	pingTimeout.restart();
	if(s.listen(port) != sf::Socket::Status::Done)
	{
		std::cout << "Failed to bind to port " << port << ", maybe already a server listening on this port?" << std::endl;
		std::cin.get();
	}
	else
	{
		acceptThread->launch();
		receiveThread->launch();
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
		PingClients();
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
			sf::Uint16 ping = PingMessage;
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

void ServerConnection::Accept()
{
	while(true)
	{
		std::cout << "Trying to accept clients..." << std::endl;
		sf::TcpSocket *tempSocket = new sf::TcpSocket();
		sf::Socket::Status status = s.accept(*tempSocket);
		if (status == sf::Socket::Done)
		{
			int freeClientId = GetFreeClientId();
			if(freeClientId != -1)
			{
				//Accept the client
				Client *client = new Client();
				client->socket = tempSocket;
				client->pingClock = sf::Clock();
				client->socket->setBlocking(false);
				client->ID = freeClientId;
				lockObject.lock();
				clients.insert(std::pair<int, Client*>(freeClientId, client));
				lockObject.unlock();
				selector.add(*client->socket);

				//Send initial init-packet to all clients
				sf::Packet packet;
				sf::Uint16 clientid = ClientID;
				packet << clientid << freeClientId;
				client->socket->send(packet);

				std::cout << client->socket->getRemoteAddress() << " connected on socket " << freeClientId << std::endl;
			}
		}
		else
		{
			switch(status)
			{
			case sf::Socket::Status::Disconnected:
				std::cout << "Error: Could not accept socket: Socket disconnected" << std::endl;
				break;
			case sf::Socket::Status::Error:
				std::cout << "Error: Could not accept socket: Random error" << std::endl;
				break;
			}
			delete tempSocket;
		}
	}
}

void ServerConnection::Receive()
{
	while(true)
	{
		if (selector.wait())
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
							packets.push(std::pair<sf::Packet*, Client*>(received, client));
						}
						//else if(status == sf::Socket::Disconnected)  //kickar klient i iteration av klientlista>.<
						//KickClient(pair.first, "Disconnected");
					}
				}
			}
			lockObject.unlock();
		}
	}
}

void ServerConnection::KickClient(int ID, std::string reason)
{
	auto client = clients.find(ID);
	if(client != clients.end())
	{
		const char *kickmsg = reason.c_str();
		sf::IpAddress ip = client->second->socket->getRemoteAddress();
		sf::Packet send;
		send << 2 << kickmsg;
		client->second->socket->send(send);
		client->second->socket->disconnect();
		lockObject.lock();
		selector.remove(*client->second->socket);
		Client *temp = clients.at(ID);
		delete temp;
		clients.erase(ID);
		currentWorld->RemovePlayer(ID);
		lockObject.unlock();
		std::cout << "Kicked client: " << ID << " Reason: " << reason << std::endl;

		send.clear();
		send << (sf::Uint16)PlayerJoinLeft << (sf::Uint16)1 << (sf::Uint16)ID;
		Broadcast(send);
		//std::cout << ip << " has left" << std::endl;
	}
}

void ServerConnection::Broadcast(sf::Packet packet)
{
	//std::cout << packet << std::endl;
	for(std::pair<int, Client*> pair : clients)
	{
		pair.second->socket->send(packet);
	}
}
