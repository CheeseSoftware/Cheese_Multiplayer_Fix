#ifndef _SERVER
#pragma once
#include <vector>
#include "GraphicalContainer.h"
#include "EventHandler.h"

class GameState;

namespace gui
{
	class IMenuItem;

	class MenuItemContainer
		: public GraphicalContainer
	{
		struct PositionItem;
		std::vector<PositionItem> itemList;
		EventHandler<GameState*> eventHandler;

	public:
		MenuItemContainer(int x, int y, int width, int height);
		virtual void EventUpdate(App &app, const sf::Event &event, GameState *gamestate);
		virtual GameState *Update(App &app);
		virtual void Draw(App &app);
		void Add(IMenuItem *item, int x, int y);
		void Remove(size_t i);
	private:
		struct PositionItem
		{
			IMenuItem * menuItem;
			int x;
			int y;
			
			PositionItem() {}

			PositionItem(IMenuItem *_menuItem, int _x, int _y)
			{
				menuItem = _menuItem;
				x = _x;
				y = _y;
			}

			~PositionItem()
			{
				delete menuItem;
			}
		};

	};
}
#endif