#include "Game.h"
#include "GameState.h"
#include "App.h"

void Game::SetGameState(GameState *gameState, bool keepMemory = false)
{
	if (!keepMemory && m_gameState)
		delete m_gameState;

	m_gameState = gameState;
}