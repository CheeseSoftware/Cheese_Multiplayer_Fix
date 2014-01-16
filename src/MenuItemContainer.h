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
		MenuItemContainer(int x, int y, int width, int height);
		virtual GameState *EventUpdate(App& app, const sf::Event& event, GameUtility* gameUtility, float x, float y);
		virtual GameState *Update(App &app);
		virtual void Draw(App &app, float drawAreax, float drawAreay, int drawAreaWidth, int drawAreaHeight);
		sf::Vector2f getSize();
		void Add(Selectable *item);
		void Remove(size_t i);
	};
}
#endif