#pragma once

class App;
namespace sf { class Event; }
class GameState;

class EventHandleable
{
#ifndef _SERVER
	virtual void HandleEvent(App &app, const sf::Event &event, GameState* gameState)=0;
#endif
};