#pragma once

#include <string>
#include <memory>

#include "CreatureController.h"
#include "EventHandleable.h"

class GameUtility;

class User : CreatureController, EventHandleable
{
public:
	User(int id);

#ifdef SERVER
	// Client-kod
#else
	virtual void HandleEvent(App &app, const sf::Event &event, GameState* gameState);
#endif
};