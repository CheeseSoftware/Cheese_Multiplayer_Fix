#include "Client.h"

Client::Client()
{
	socket = new sf::TcpSocket();
	//hasConnectedProperly = false;
}

Client::~Client()
{
	delete socket;
}