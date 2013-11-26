#ifndef _SERVER
#include <SFML\Graphics.hpp>
#include "App.h"
#include "IMenuItem.h"
#include "GameState.h"
#include "MenuItemContainer.h"
#include <iostream>

namespace gui
{
	MenuItemContainer::MenuItemContainer(int x, int y, int width, int height)
		: GraphicalContainer(x, y, width, height)
	{
		itemList = new std::vector<Selectable*>();
	}

	void MenuItemContainer::EventUpdate(App &app, const sf::Event &event, GameState *gamestate)
	{
		eventHandler.EventUpdate(app, event, gamestate);
	}

	GameState *MenuItemContainer::Update(App &app)
	{
		for (Selectable *i : *itemList)
			i->Update(app);
		return nullptr;
	}

	void MenuItemContainer::Draw(App &app)
	{
		for (Selectable *i : *itemList)
			i->Draw(app, i->getPosition().x + m_x, i->getPosition().y + m_y);
	}

	void MenuItemContainer::Add(Selectable *item)
	{
		itemList->push_back(item);
	}

	void MenuItemContainer::Remove(size_t i)
	{
		itemList->erase(itemList->begin() + i);
	}

}
#endif