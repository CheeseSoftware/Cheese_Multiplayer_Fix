#ifndef _SERVER
#pragma once
#include <SFML/Graphics.hpp>
#include "Selectable.h"
#include "Selectable.h"

namespace gui
{
	class Label
		: public Selectable
	{
	public:
		Label(int x, int y, int width, int height, sf::String *text, sf::Font *font);
		~Label();
		virtual GameState *EventUpdate(App& app, const sf::Event& event, GameState* gameState, float x, float y);
		virtual void Draw(App &app, float drawAreax, float drawAreay, int drawAreaWidth, int drawAreaHeight);
		sf::Text *text;
	};
}

#endif