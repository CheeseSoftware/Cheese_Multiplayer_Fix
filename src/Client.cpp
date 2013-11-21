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
	delete socket;
}