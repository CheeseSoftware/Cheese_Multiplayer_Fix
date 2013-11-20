#include "ServerConnection.h"

ServerConnection::ServerConnection(int port, World *world)
{
	currentWorld = world;
	//maxClients = 1024;
	s.setBlocking(false);
	pingTimeout.restart();
	if(s.listen(port) != sf::Socket::Status::Done)
	{
		std::cout << "Failed to bind to port " << port << ", maybe already a server listening on this port?" << std::endl;
		std::cin.get();
	}
	else
		std::cout << "Server listening to port " << port << std::endl;
}


ServerConnection::~ServerConnection(void)
{
}

void ServerConnection::Run(void)
{
	Accept();
	Receive();

	float ElapsedTime = pingTimeout.getElapsedTime().asMilliseconds();
	if(ElapsedTime > 1)
	{
		pingTimeout.restart();
		PingClients();
	}
}

void ServerConnection::PingClients(void)
{
	for(std::pair<int, Client*> pair : clients)
	{
		Client *client = pair.second;
		sf::Packet send;
		sf::Uint16 ping = 1;
		send << ping;
		client->socket->send(send);
		client->pingClock.restart();
	}
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
			clients.insert(std::pair<int, Client*>(freeClientId, client));

			//Send initial init-packet to all clients
			sf::Packet packet;
			sf::Uint16 clientid = ClientID;
			packet << clientid << freeClientId;
			client->socket->send(packet);

			std::cout << client->socket->getRemoteAddress() << " connected on socket " << freeClientId << std::endl;
			return;
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
	}
	delete tempSocket;
}

void ServerConnection::Receive()
{
	for(std::pair<int, Client*> pair : clients)
	{
		Client *client = pair.second;
		//sf::TcpSocket* socket = client->socket;
		//std::cout << "hasconnected " << client->hasConnectedProperly << std::endl;
		if(client->socket->getRemoteAddress() !=sf::IpAddress::None)
		{
			sf::Packet *received = new sf::Packet();
			sf::Socket::Status status = client->socket->receive(*received);
			if (status == sf::Socket::Done)
			{
				packets.push(std::pair<sf::Packet*, Client*>(received, client));
				//std::cout << "Client " << i << " says: " << *received << " with a size of " << received->GetDataSize() << std::endl;
			}
			else if(status == sf::Socket::Disconnected)
				KickClient(pair.first, "Disconnected");
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
		clients.erase(ID);
		currentWorld->RemovePlayer(ID);
		std::cout << "Kicked client " << ID << " - " << reason << std::endl;

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
