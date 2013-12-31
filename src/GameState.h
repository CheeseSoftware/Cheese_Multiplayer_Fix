#pragma once

class GameState;

#include <SFML\Graphics.hpp>
#include "App.h"

#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

//#include <SFML/Graphics.hpp>

class GameState {
public:
    //virtual void Initialize()=0;
    virtual GameState *Update(App &app)=0; // ,Callbacks &callbacks)... hmm.. Kanske ska App ha callbacks?
#ifndef _SERVER
	virtual void EventUpdate(App &app, const sf::Event &event)=0; // ^^ samma h�r
    virtual void Draw(App &app)=0; // d� f�r draw ocks� callbacksXD, fast "error"-callback b�r ju kunna ske d�r med! Men varf�r ska man hantera error olika? tr {} catch{} finally{} FUNKAR!
#endif
    //virtual void Shutdown()=0;
};

#endif // GAMESTATE_H_INCLUDED
