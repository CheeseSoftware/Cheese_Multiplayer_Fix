#ifndef _SERVER
#include <SFML\Graphics.hpp>
#include "App.h"
#include "IMenuItem.h"
#include "GameState.h"
#include "MenuItemContainer.h"
#include <iostream>

namespace gui
{
	MenuItemContainer::MenuItemContainer(int x, int y)
		: Selectable(x, y)
	{
		itemList = new std::vector<Selectable*>();
	}

	GameState *MenuItemContainer::EventUpdate(App &app, const sf::Event &event, GameState *gamestate)
	{
		eventHandler.EventUpdate(app, event, gamestate);
		return nullptr;
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