#pragma once
#include <functional>
class GameState;

struct MainCallbacks
{
	std::function<void (GameState *)> SetGameState;
	std::function<void ()> Exit;
	std::function<void ()> Restart;
};