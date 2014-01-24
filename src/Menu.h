#pragma once

#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "GameState.h"
class AMenuState;

class Menu : public GameState
{
private:
    GameState *menuState;
public:
	Menu();
	~Menu();
    //virtual void Initialize();
    virtual void EventUpdate(App &app, Game &game, const sf::Event &event);
    virtual GameState *Update(App &app, Game &game);
    virtual void Draw(App &app);
    //virtual void Shutdown();
};

#endif // MENU_H_INCLUDED
