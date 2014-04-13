#ifdef SERVER
#include "GameServer.h"
#include "GameState.h"
#include "App.h"
#include "ServerState.h"

GameServer::GameServer()
{

}

GameServer::~GameServer()
{

}


void GameServer::Run()
{
	app = new App();

	m_gameState = nullptr;
	Restart();

	do
	{
		app->Update();
	}
	while (m_gameState->Update(*app, this));
}

void GameServer::Exit()
{
	m_gameState = nullptr;
}

void GameServer::Restart()
{
	if (m_gameState)
		delete m_gameState;

	m_gameState = new ServerState(*app);
}
#endif