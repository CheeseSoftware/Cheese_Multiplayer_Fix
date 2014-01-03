#ifndef _SERVER

#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "MainMenu.h"
#include "GameState.h"

Menu::Menu()//void Menu::Initialize()
{
    menuState = new MainMenu();
    //menuState->Initialize();
}

Menu::~Menu()//void Menu::Shutdown()
{
    //menuState->Shutdown();
    delete menuState;
}

void Menu::EventUpdate(App &app, Game &game, const sf::Event &event)
{
    menuState->EventUpdate(app, game, event);
}

GameState *Menu::Update(App &app, Game &game)
{
	GameState *newState = menuState->Update(app, game);
	if (newState != menuState)
    {
		if (dynamic_cast<MenuState*>(newState) != 0)
		{
			return newState;
		}
		else
		{
			//menuState->Shutdown();
			delete menuState;
			menuState = newState;
			//menuState->Initialize();
		}
    }
    return this;
}

void Menu::Draw(App &app)
{
    menuState->Draw(app);
}

#endif