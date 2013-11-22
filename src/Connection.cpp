#include "Connection.h"

Connection::Connection(int port, sf::IpAddress ip)
{
	client = new Client();
	receiveThread = new sf::Thread(&Connection::Receive, this);
	if(client->socket->connect(ip, port, sf::Time(sf::seconds(5))) == sf::Socket::Done)
	{
		selector.add(*client->socket);
		receiveThread->launch();

		//vänta-saker börjar här
		sf::Clock *c = new sf::Clock();
		c->restart();
		while(c->getElapsedTime() < sf::milliseconds(500)) {} //Måste vänta tills servern har lagt till klienten ordentligt
		delete c;
		//vänta-saker slutar här

		sf::Packet packet;
		packet << (sf::Uint16)RequestInit;
		client->socket->send(packet);
		std::cout << "Connected to " << ip << " : " << port << std::endl;
	}
	else
	{
		std::cout << "Error connecting to " << ip << " : " << port << std::endl;
		std::cin.get();
	}
}


Connection::~Connection(void)
{
}

void Connection::Run()
{

}

void Connection::Receive()
{
	while(true)
	{
		if(selector.wait())
		{
			if(selector.isReady(*client->socket))
			{
				sf::Packet *received = new sf::Packet();
				if (client->socket->receive(*received) == sf::Socket::Done)
				{
					globalMutex.lock();
					packets.push(received);
					globalMutex.unlock();
				}
				else
				{
					//std::cout << "Failed to receive data from sending server!" << std::endl;
					delete received;
				}
			}
		}
	}
}