#ifndef _SERVER

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "MenuState.h"
//#include "MenuItem.h"                            
#include "GameState.h"
#include "IMenuItem.h"
#include "Text.h"
#include "MenuItemContainer.h"

MenuState::MenuState()// : menuItemContainer(0, 0, 100, 100)//void MenuState::Initialize()
{
	menuItemContainer = new gui::MenuItemContainer(0, 0, 100, 100);
}

MenuState::~MenuState()//void MenuState::Shutdown()
{
	//for (std::vector<double>::size_type i = 0; i < menuItems.size(); i++)
	{
		//    delete menuItems[i];
	}
}

void MenuState::EventUpdate(App &app, const sf::Event &event)
{
	menuItemContainer->EventUpdate(app, event, this);//eventHandler.EventUpdate(app, event, this);
}

GameState *MenuState::Update(App &app)
{
	return this;
}

void MenuState::Draw(App &app)
{
	menuItemContainer->Draw(app);
}
#endif