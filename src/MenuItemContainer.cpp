#ifndef _SERVER
#include <SFML\Graphics.hpp>
#include "App.h"
#include "IMenuItem.h"
#include "GameState.h"
#include "MenuItemContainer.h"

namespace gui
{
	MenuItemContainer::MenuItemContainer(int x, int y, int width, int height)
		: GraphicalContainer(x, y, width, height)
	{

	}

	void MenuItemContainer::EventUpdate(App &app, const sf::Event &event, GameState *gamestate)
	{
		eventHandler.EventUpdate(app, event, gamestate);
	}

	GameState *MenuItemContainer::Update(App &app)
	{
		return nullptr;
	}

	void MenuItemContainer::Draw(App &app)
	{
		for (auto i : itemList)
			i.menuItem->Draw(app, i.x, i.y);
	}

	void MenuItemContainer::Add(IMenuItem *item, int x, int y)
	{
		itemList.push_back(PositionItem(item, x, y));
	}

	void MenuItemContainer::Remove(size_t i)
	{
		itemList.erase(itemList.begin() + i);
	}

}
#endif