#ifndef _SERVER
#pragma once
#include <vector>
#include "EventHandler.h"
#include "Selectable.h"

class GameState;

namespace gui
{
	class IMenuItem;

	class MenuItemContainer
		: public Selectable
	{
		std::vector<Selectable*> *itemList;
		EventHandler<GameState*> eventHandler;

	public:
		MenuItemContainer(int x, int y);
		virtual GameState *EventUpdate(App &app, const sf::Event &event, GameState *gamestate);
		virtual GameState *Update(App &app);
		virtual void Draw(App &app);
		void Add(Selectable *item);
		void Remove(size_t i);
	};
}
#endif