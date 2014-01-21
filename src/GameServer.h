#ifdef SERVER
#pragma once

#include "Game.h"

class GameServer : public Game
{
	App *app;
public:
	GameServer();
	~GameServer();

	virtual void Run();
	virtual void Exit();
	virtual void Restart();
};
#endif