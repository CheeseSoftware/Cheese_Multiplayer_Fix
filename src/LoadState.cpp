#ifdef CLIENT
#include "LoadState.h"
#include "Connection.h"
#include "PlayState.h"

extern int _argc;
extern char** _argv;

LoadState::LoadState(App &app, GameState *gameState, GameState *oldState)
	: m_gameState(gameState)
	, m_oldState(oldState)
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

bool LoadState::Load()
{
	return  true;
}

void LoadState::EventUpdate(App &app, Game &game, const sf::Event &event)
{
}

GameState *LoadState::Update(App &app, Game &game)
{
	return (new PlayState(*(PlayState*)this));
}

void LoadState::Draw(App &app)
{
}
#endif
