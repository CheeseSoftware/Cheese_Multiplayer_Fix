#ifdef CLIENT

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "AMenuState.h"
//#include "MenuItem.h"                            
#include "GameState.h"
#include "IMenuItem.h"
#include "Text.h"
#include "MenuItemContainer.h"

AMenuState::AMenuState()// : menuItemContainer(0, 0, 100, 100)//void AMenuState::Initialize()
{
	menuItemContainer = new gui::MenuItemContainer(0, 0, 0, 0);
}

AMenuState::~AMenuState()//void AMenuState::Shutdown()
{
	//for (std::vector<double>::size_type i = 0; i < menuItems.size(); i++)
	{
		//    delete menuItems[i];
	}
}

void AMenuState::EventUpdate(App &app, Game &game, const sf::Event &event)
{
	if (event.type == sf::Event::Resized)
	{
		app.setView(sf::View(sf::FloatRect(0, 0, app.getSize().x, app.getSize().y)));
	}

	menuItemContainer->EventUpdate(app, event, 0, 0);//eventHandler.EventUpdate(app, event, this);
}

GameState *AMenuState::Update(App &app, Game &game)
{
	return this;
}

void AMenuState::Draw(App &app)
{
	menuItemContainer->Draw(app, 0, 0, 0, 0);
}
#endif