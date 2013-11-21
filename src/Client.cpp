#include "Client.h"

Client::Client()
{
	socket = new sf::TcpSocket();
	isMeasuringPing = false;
	pingClock.restart();
	//hasConnectedProperly = false;
}

Client::~Client()
{
	if (socket != nullptr)
	{
		socket->disconnect();
	}
	delete socket;
}