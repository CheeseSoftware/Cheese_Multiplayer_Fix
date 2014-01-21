#ifdef CLIENT
#pragma once

#include "Game.h"

class GameClient : public Game
{
	App *app;
public:
	GameClient();
	~GameClient();

	virtual void Run();
	virtual void Exit();
	virtual void Restart();
};
#endif