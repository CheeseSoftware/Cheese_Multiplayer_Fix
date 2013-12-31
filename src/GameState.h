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
	virtual void EventUpdate(App &app, const sf::Event &event)=0; // ^^ samma här
    virtual void Draw(App &app)=0; // då får draw också callbacksXD, fast "error"-callback bör ju kunna ske där med! Men varför ska man hantera error olika? tr {} catch{} finally{} FUNKAR!
#endif
    //virtual void Shutdown()=0;
};

#endif // GAMESTATE_H_INCLUDED
