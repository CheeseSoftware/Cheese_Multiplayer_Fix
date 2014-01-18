

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

	//////////////////////////////////////////////////////////////////////////////////////////
#include "User.h"

int _argc;
char** _argv;

int main(int argc, char** argv)
{
	_argc = argc;
	_argv = argv;

#ifdef _SERVER
	GameServer game;
#else
	GameClient game;
#endif

	game.Run();

	return 0;
}