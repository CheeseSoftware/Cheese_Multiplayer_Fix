#ifdef SERVER
#pragma once

#include "Game.h"
#include "SoundHandler.h"
#include "TextureContainer.h"

class GameServer : public Game, public SoundHandler, public TextureContainer
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