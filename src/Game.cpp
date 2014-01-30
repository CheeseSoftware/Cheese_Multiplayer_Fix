#include "Game.h"
#include "GameState.h"
#include "App.h"

//
#include <iostream>
//

void Game::SetGameState(GameState *gameState, bool keepMemory)
{
	if (!keepMemory && m_gameState)
		delete m_gameState;

	m_gameState = gameState;

		std::cout << "new gamestate: " << m_gameState << std::endl;

	if (m_gameState)
		std::cout << "new gamestate: "<< typeid(*m_gameState).name() << std::endl;
}