#pragma once

class GameState;
class App;

class Game
{
protected:
	GameState *m_gameState;
public:
	virtual void Run()=0;

	void SetGameState(GameState *gameState, bool keepMemory=false);
	virtual void Exit()=0;
	virtual void Restart()=0;
};