#pragma once

class GameState;

#include <SFML\Graphics.hpp>
#include <functional>
<<<<<<< HEAD
<<<<<<< HEAD
#include <queue>

#include "App.h"
=======
>>>>>>> 2a6a571db8852cc399d4eb3e31fa1cb2c0420122
=======
>>>>>>> 2a6a571db8852cc399d4eb3e31fa1cb2c0420122
#include "MainCallbacks.h"
class Game;
class App;

#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

//#include <SFML/Graphics.hpp>

class GameState
{
	std::queue<std::function<void(App &app, Game &game)>> invokeQueue;
public:
	virtual bool Load(){return true;};
    virtual GameState *Update(App &app, Game &game); // ,Callbacks &game)... hmm.. Kanske ska App ha game?
#ifdef CLIENT
	virtual void EventUpdate(App &app, Game &game, const sf::Event &event)=0; // ^^ samma h�r
    virtual void Draw(App &app)=0; // d� f�r draw ocks� gameXD, fast "error"-callback b�r ju kunna ske d�r med! Men varf�r ska man hantera error olika? tr {} catch{} finally{} FUNKAR!
#endif
	void Invoke(std::function<void(App &app, Game &game)> function);
    //virtual void Shutdown()=0;
};

#endif // GAMESTATE_H_INCLUDED
