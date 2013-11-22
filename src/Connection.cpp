#include "Connection.h"

Connection::Connection(int port, sf::IpAddress IP)
{
	client = new Client();
	//thread = new sf::Thread(&Connection::Run);
	if(Connect(IP, port))
	{
		//thread->launch();
	}
}

Connection::~Connection(void)
{
}

void Connection::Run()
{
	//while(true)
	{
		Receive();

		//sf::sleep(sf::milliseconds(10));
	}
}

bool Connection::Connect(sf::IpAddress ip, int port)
{
	if(client->socket->connect(ip, port, sf::Time(sf::seconds(5))) == sf::Socket::Done)
	{
		client->socket->setBlocking(false);
		std::cout << "Connected to " << ip << " : " << port << std::endl;

		//v�nta-saker b�rjar h�r
		sf::Clock *c = new sf::Clock();
		c->restart();
		while(c->getElapsedTime() < sf::milliseconds(500)) {} //M�ste v�nta tills servern har lagt till klienten ordentligt
		delete c;
		//v�nta-saker slutar h�r

		sf::Packet packet;
		packet << (sf::Uint16)RequestInit;
		client->socket->send(packet);
		return(true);
	}
	else
	{
		std::cout << "Error connecting to " << ip << " : " << port << std::endl;
		return(false);
	}
}

void Connection::Receive()
{
	if(&client->socket != nullptr)
	{
		sf::Packet *received = new sf::Packet();
		sf::Socket::Status status = client->socket->receive(*received);
		if (status == sf::Socket::Done)
		{
			globalMutex.lock();
			packets.push(received);
			globalMutex.unlock();
		}
	}
}