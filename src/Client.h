#pragma once

#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include "MessageType.h"

class Client
{
public:
	Client(void);
	~Client(void);
	//bool hasConnectedProperly;
	sf::TcpSocket *socket;
	sf::Uint16 ID;
	std::string name;
	sf::Uint16 ping;
	sf::Clock pingClock;
};

