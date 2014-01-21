#ifdef CLIENT
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "PlayState.h"
#include "MainMenu.h"
#include "GameClient.h"
#else
#include "ServerState.h"
#include "GameServer.h"
#endif
#include "App.h"
#include "User.h"

int _argc;
char** _argv;

int main(int argc, char** argv)
{
	_argc = argc;
	_argv = argv;

#ifdef SERVER
	GameServer game;
#else
	GameClient game;
#endif

	game.Run();
	return 0;
}