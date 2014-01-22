#pragma once

#ifndef MAINMENU_H_INCLUDED
#define MAINMENU_H_INCLUDED

#include "AMenuState.h"
#include "GameState.h"

class Game;

class MainMenu : public AMenuState
{
public:
	MainMenu(Game *game);
    ~MainMenu();
    //virtual void Initialize();
    virtual void EventUpdate(App &app, Game &game, const sf::Event &event);
    virtual GameState *Update(App &app, Game &game);
    virtual void Draw(App &app);
    //virtual void Shutdown();
};

#endif // MAINMENU_H_INCLUDED
