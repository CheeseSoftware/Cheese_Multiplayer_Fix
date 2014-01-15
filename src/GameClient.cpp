#ifndef _SERVER

#include "GameClient.h"
#include "GameState.h"
#include "App.h"
#include "PlayState.h"
#include "MainMenu.h"

GameClient::GameClient()
{

}

GameClient::~GameClient()
{

}


void GameClient::Run()
{
	app = new App(sf::VideoMode(1152,720));

	m_gameState = nullptr;
	Restart();

	while (app->isOpen())
	{
		sf::Event event;
		while (app->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				app->close();
			

			m_gameState->EventUpdate(*app, *this, event);
			// Pass the event to all the objects (if there would be objects)
            //app.handleEvent(event);
		}

		app->Update(); 
		m_gameState->Update(*app, *this);

		app->clear();

		m_gameState->Draw(*app);

		app->display();
	}

}

void GameClient::Exit()
{
	m_gameState = nullptr;
}

void GameClient::Restart()
{
	if (m_gameState)
		delete m_gameState;

	m_gameState = new MainMenu(this);//new PlayState(*app);//
}
#endif