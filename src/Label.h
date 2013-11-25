#ifndef _SERVER
#pragma once
#include <SFML/Graphics.hpp>
#include "GUIItem.h"
#include "Selectable.h"

namespace gui
{
	class Label
		: public virtual GUIItem, public sf::Text
	{
	public:
		Label(int x, int y, /*ClickEvent &clickEvent, */sf::String text, sf::Font font);
		~Label();
		virtual void OnLeftClick(App &app, const sf::Event &event, GameState *gameState);
		virtual void OnRightClick(App &app, const sf::Event &event, GameState *gameState);
		virtual GameState *EventUpdate(App &app, const sf::Event &event, GameState *gameState);
		virtual void Draw(App &app, float x, float y) const;
	};
}

#endif