#pragma once

class GameState;

#include <SFML\Graphics.hpp>
#include <functional>
#include <queue>
#include <mutex>

#include "App.h"
#include "MainCallbacks.h"
class Game;
class App;

#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

//#include <SFML/Graphics.hpp>

class GameState
{
	std::queue<std::function<void(App &app, Game *game)>> invokeQueue;
	std::mutex *invokeLock;
public:
	GameState();
	virtual bool Load(Game *game){return true;};
    virtual GameState *Update(App &app, Game *game); // ,Callbacks &game)... hmm.. Kanske ska App ha game?
#ifdef CLIENT
	virtual void EventUpdate(App &app, Game *game, const sf::Event &event)=0; // ^^ samma h�r
    virtual void Draw(App &app, Game *game)=0; // d� f�r draw ocks� gameXD, fast "error"-callback b�r ju kunna ske d�r med! Men varf�r ska man hantera error olika? tr {} catch{} finally{} FUNKAR!
#endif
	void Invoke(std::function<void(App &app, Game *game)> function);
    //virtual void Shutdown()=0;
	//GameState &operator =(  GameState const& other );
};

#endif // GAMESTATE_H_INCLUDED
