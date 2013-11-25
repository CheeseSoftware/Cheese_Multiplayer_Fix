#ifndef _SERVER
#pragma once
#include "GameUtility.h"
#include "GameState.h"
#include "Connection.h"

class LoadState : public GameUtility
{
public:
	LoadState(App &app);
	~LoadState(void);
	virtual void EventUpdate(App &app, const sf::Event &event);
	virtual GameState *Update(App &app);
	virtual void Draw(App &app);
	Connection *connection;
};
#endif

