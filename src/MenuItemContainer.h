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
<<<<<<< HEAD
		virtual GameState *EventUpdate(App& app, const sf::Event& event, GameUtility* gameUtility, float x, float y);
		virtual GameState *Update(App &app);
=======
		virtual GameState *EventUpdate(App& app, const sf::Event& event, float x, float y);
		virtual GameState *Update(App &app, Game &game);
>>>>>>> c953a28c2ff85939864a8166e4b9475db0da2b73
		virtual void Draw(App &app, float drawAreax, float drawAreay, int drawAreaWidth, int drawAreaHeight);
		sf::Vector2f getSize();
		void Add(Selectable *item);
		void Remove(size_t i);
	};
}
#endif