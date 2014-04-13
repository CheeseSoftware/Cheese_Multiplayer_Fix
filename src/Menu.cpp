#ifdef CLIENT

#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "MainMenu.h"
#include "GameState.h"

Menu::Menu()//void Menu::Initialize()
{
    //AMenuState = new MainMenu();
    //menuState->Initialize();
}

Menu::~Menu()//void Menu::Shutdown()
{
    //menuState->Shutdown();
    //delete AMenuState;
}

void Menu::EventUpdate(App &app, Game *game, const sf::Event &event)
{
    //AMenuState->EventUpdate(app, game, event);
}

GameState *Menu::Update(App &app, Game *game)
{
	/*GameState *newState = AMenuState->Update(app, game);
	if (newState != AMenuState)
    {
		if (dynamic_cast<MenuState*>(newState) != 0)
		{
			return newState;
		}
		else
		{
			//menuState->Shutdown();
			delete AMenuState;
			menuState = newState;
			//menuState->Initialize();
		}
    }*/
    return this;
}

void Menu::Draw(App &app, Game *game)
{
    //AMenuState->Draw(app);
}

#endif