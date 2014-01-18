#pragma once

#include <functional>

#include "GameState.h"

struct MainCallbacks
{
	std::function<void (GameState *)> SetGameState;
	std::function<void ()> Exit;
	std::function<void ()> Restart;
};