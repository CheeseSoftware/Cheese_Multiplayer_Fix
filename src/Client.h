#pragma once

#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include "MessageType.h"

class Client
{
private:
#ifdef _SERVER
	//setd::vector<std::pair<long, long>> chunks;
	long chunkX;
	long chunkY;
	bool *chunks;
#endif
public:
	Client(void);
	~Client(void);
	//bool hasConnectedProperly;
	sf::TcpSocket *socket;
	sf::Uint16 ID;
	std::string name;
	float ping;
	sf::Clock pingClock;
	bool isMeasuringPing;
	void Move(char x, char y);
};

