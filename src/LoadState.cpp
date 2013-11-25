#ifndef _SERVER
#include "LoadState.h"
#include "Connection.h"
#include "PlayState.h"

extern int _argc;
extern char** _argv;

LoadState::LoadState(App &app)
	: GameUtility(app)
{
	char* str_ip = "127.0.0.1";

	if (_argc >= 2)
	{
		str_ip = _argv[1];
	}
	std::cout << "Connecting to " << str_ip << " ...\n";

	sf::IpAddress ip(str_ip);//std::string ip;
	int port;
	//connection = new Connection(5001, ip, this);
}


LoadState::~LoadState(void)
{
}

void LoadState::EventUpdate(App &app, const sf::Event &event)
{
}

GameState *LoadState::Update(App &app)
{
	return (new PlayState(*(PlayState*)this));
}

void LoadState::Draw(App &app)
{
}
#endif