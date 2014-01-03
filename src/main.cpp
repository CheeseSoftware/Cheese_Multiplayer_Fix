

#ifndef _SERVER
//#include <functional>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "PlayState.h"
#include "MainMenu.h" //
//#include "MainMenu.h"
#else
#include "ServerState.h"

#endif
#include "App.h"
#include "GameClient.h"
#include "GameServer.h"

int _argc;
char** _argv;

int main(int argc, char** argv)
{
	_argc = argc;
	_argv = argv;

#ifdef _SERVER
	GameServer game;

	//hile (game.Update(app));
#else
	GameClient game;

	/*while (app.isOpen())
	{
		if(!game.Update(app))
			break;

		game.Draw(app);
	}*/
#endif

	game.Run();

	return 0;
}

/*CLIENT(
void RenderingThread(App *app, GameState *gameState);
)

int _argc;
char** _argv;
//using namespace sf;

/*#ifdef _SERVER
#define _APP *reinterpret_cast<tgui::Window*>(&app)//static_cast<tgui::Window>(app)
#else
#define _APP app
#endif* /

int main(int argc, char** argv)
{
	_argc = argc;
	_argv = argv;



#ifndef _SERVER

	App app(sf::VideoMode(1152,720));

	//GameState *gameState = new MainMenu();
	GameState *gameState = new PlayState((const PlayState&)app);
#else
	App app;
	GameState *gameState = new ServerState(app);
#endif

	GameState *oldState;

	MainCallbacks *game = new MainCallbacks();
	game->Exit = [&]()
	{
		gameState = nullptr;
	};
	game->Restart = []()
	{
		std::cout << "Restart() does not exist.\n";
	};
	game->SetGameState = [&](GameState *newGameState)
	{
		gameState = newGameState;
	};

	//app.SetFramerateLimit(6);

#ifndef _SERVER
	/*app.setActive(false);
	sf::Thread renderingThread(std::bind(&RenderingThread, &app, gameState));
	renderingThread.launch();* /

	while (app.isOpen())
	{
		sf::Event event;
		while (app.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				app.close();
			

			gameState->EventUpdate(app, game, event);
			// Pass the event to all the objects (if there would be objects)
            //app.handleEvent(event);
		}
#else
	while (true)
	{
#endif

		oldState = gameState;
		if((gameState=gameState->Update(app, game)) != oldState)
		{
			delete oldState;
		}

		app.Update();

		CLIENT(RenderingThread(&app, gameState);)
	}

	return 0;
}

CLIENT(
void RenderingThread(App *app, GameState *gameState)
{
	//while(app->isOpen())
	{
		app->clear();

		gameState->Draw(*app);

		//app->Update();
		app->display();
	}
})*/