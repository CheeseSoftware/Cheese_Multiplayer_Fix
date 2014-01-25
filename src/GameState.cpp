#include "GameState.h"

GameState::GameState()
{
	GameState::invokeLock = new std::mutex();
}

GameState *GameState::Update(App &app, Game &game)
{
	invokeLock->lock();
	while(!invokeQueue.empty())
	{
		invokeQueue.front()(app, game);
		invokeQueue.pop();
	}
	invokeLock->unlock();

	return this;
}

void GameState::Invoke(std::function<void(App& app, Game &game)> function)
{
	invokeLock->lock();
	invokeQueue.push(function);
	invokeLock->unlock();
}

/*GameState &GameState::operator =( GameState const& other )
{
	// keep my own mutex
	//invokeLock = other.invokeLock.; // maybe sync this?
	return *this;
}*/