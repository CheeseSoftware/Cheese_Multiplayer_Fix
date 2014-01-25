#include "GameState.h"

GameState *GameState::Update(App &app, Game &game)
{
	while(!invokeQueue.empty())
	{
		invokeQueue.front()(app, game);
		invokeQueue.pop();
	}

	return this;
}

void GameState::Invoke(std::function<void(App& app, Game &game)> function)
{
	invokeQueue.push(function);
}