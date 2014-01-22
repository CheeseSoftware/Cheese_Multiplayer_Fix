#ifdef CLIENT
#pragma once
#include "GameState.h"
#include "Connection.h"

class LoadState : public GameState
{
	GameState *m_gameState;
	GameState *m_oldState;
public:
	LoadState(App &app, GameState *gameState, GameState *oldState/*>_< , sf::Time animationLength = 250ms, ScreenAnimation animation = new BLASTANDARD()*/);
	~LoadState(void); 
	virtual bool Load();
	virtual void EventUpdate(App &app, Game &game, const sf::Event &event);
	virtual GameState *Update(App &app, Game &game);
	virtual void Draw(App &app);
};
#endif