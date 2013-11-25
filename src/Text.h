#ifndef _SERVER
#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "GUIItem.h"
#include "GameState.h"
#include "App.h"

namespace gui
{
	class Text : public GUIItem
	{
	public:
		//std::string text;
		Text(sf::Text *text);//Label(int x, int y, int width, int height, std::function<GameState*(App&)> &clickEvent, std::string text);
		~Text();
		virtual GameState *EventUpdate(App& app, const sf::Event& event, GameState* gameState);
		//virtual void Draw(App &app);
	};
}

#endif