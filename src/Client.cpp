#include "Client.h"

Client::Client()
{
	socket = new sf::TcpSocket();
	isMeasuringPing = false;
	pingClock.restart();
}

Client::~Client()
{
	if (socket != nullptr)
	{
		socket->disconnect();
	}
	delete socket;
}