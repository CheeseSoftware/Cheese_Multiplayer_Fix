#pragma once

class App;
namespace sf { class Event; }
class GameState;

class EventHandleable
{
#ifdef CLIENT
	virtual void HandleEvent(App &app, const sf::Event &event, GameState* gameState)=0;
#endif
};