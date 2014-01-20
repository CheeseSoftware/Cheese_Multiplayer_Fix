#pragma once

class GameState;

#include <SFML\Graphics.hpp>
#include <functional>

#include "App.h"
#include "MainCallbacks.h"
#include "Game.h"

#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

//#include <SFML/Graphics.hpp>

class GameState
{
public:
	virtual bool Load()=0;
    virtual GameState *Update(App &app, Game &game)=0; // ,Callbacks &game)... hmm.. Kanske ska App ha game?
#ifndef _SERVER
	virtual void EventUpdate(App &app, Game &game, const sf::Event &event)=0; // ^^ samma h�r
    virtual void Draw(App &app)=0; // d� f�r draw ocks� gameXD, fast "error"-callback b�r ju kunna ske d�r med! Men varf�r ska man hantera error olika? tr {} catch{} finally{} FUNKAR!
#endif
    //virtual void Shutdown()=0;
};

#endif // GAMESTATE_H_INCLUDED
