#ifdef MENUIDIOTI
#pragma once
#ifndef _SERVER

#include <SFML/Graphics.hpp>
#include "TextItem.h"
#include "Selectable.h"

namespace gui
{
	class Label
		: public virtual Selectable, public virtual TextItem //public virtual positionItem, public virtual Text
	{
	public:
		std::string text;
		Label(int x, int y, ClickEvent &clickEvent, sf::Text &text);
		~Label();

		virtual void OnLeftClick(App &app, const sf::Event &event, GameState *gameState);

		virtual void OnRightClick(App &app, const sf::Event &event, GameState *gameState);

		//virtual GameState *EventUpdate(App& app, const sf::Event& event, GameState* gameState);
		//virtual void Draw(App &app);
	};
}

#endif
#endif