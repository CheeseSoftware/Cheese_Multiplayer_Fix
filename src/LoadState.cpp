#ifdef CLIENT
#include <thread>
#include "LoadState.h"
#include "Connection.h"
#include "PlayState.h"
#include "Game.h"

extern int _argc;
extern char** _argv;

LoadState::LoadState(App &app, Game *game, GameState *gameState, GameState *oldState)
	: m_gameState(gameState)
	, m_oldState(oldState)
{
	/*char* str_ip = "127.0.0.1";

	if (_argc >= 2)
	{
		str_ip = _argv[1];
	}
	std::cout << "Connecting to " << str_ip << " ...\n";

	sf::IpAddress ip(str_ip);//std::string ip;
	int port;*/
	//connection = new Connection(5001, ip, this);
	Load(game);
}


LoadState::~LoadState(void)
{
}

bool LoadState::Load(Game *game)
{
	thread = new std::thread([this, game]()
	{
		bool success = m_gameState->Load(game);
		//if (!success)
		//	success = m_oldState->Load(Game *game);
		std::cout<<this<<std::endl;
		if (success)
		{
			delete m_oldState;
			Invoke([this](App &app, Game *game){ game->SetGameState(m_gameState); });
		}
		else
		{
			Invoke([this](App &app, Game *game){ game->SetGameState(m_oldState); });
			delete m_gameState;
		}
	});
	return  true;
}

void LoadState::EventUpdate(App &app, Game *game, const sf::Event &event)
{
}

GameState *LoadState::Update(App &app, Game *game)
{
	GameState::Update(app, game);

	return nullptr;
}

void LoadState::Draw(App &app, Game *game)
{
}
#endif
