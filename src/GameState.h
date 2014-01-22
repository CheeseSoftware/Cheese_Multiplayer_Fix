#pragma once

class GameState;

#include <SFML\Graphics.hpp>
#include <functional>
#include "MainCallbacks.h"
class Game;
class App;

#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

//#include <SFML/Graphics.hpp>

class GameState
{
public:
	virtual bool Load(){return true;};
    virtual GameState *Update(App &app, Game &game)=0; // ,Callbacks &game)... hmm.. Kanske ska App ha game?
#ifdef CLIENT
	virtual void EventUpdate(App &app, Game &game, const sf::Event &event)=0; // ^^ samma här
    virtual void Draw(App &app)=0; // då får draw också gameXD, fast "error"-callback bör ju kunna ske där med! Men varför ska man hantera error olika? tr {} catch{} finally{} FUNKAR!
#endif
    //virtual void Shutdown()=0;
};

#endif // GAMESTATE_H_INCLUDED
