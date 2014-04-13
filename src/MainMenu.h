#ifdef CLIENT
#pragma once

#include "AMenuState.h"
#include "GameState.h"
#include "SoundHandler.h"

class Game;

class MainMenu : public AMenuState
{
	SoundHandler soundHandler;
public:
	MainMenu(Game *game);
    ~MainMenu();
    //virtual void Initialize();
    virtual void EventUpdate(App &app, Game *game, const sf::Event &event);
    virtual GameState *Update(App &app, Game *game);
    virtual void Draw(App &app, Game *game);
    //virtual void Shutdown();
};

#endif // MAINMENU_H_INCLUDED
