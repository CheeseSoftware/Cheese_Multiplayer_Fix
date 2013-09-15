/*#pragma once
#ifndef _SERVER

#include <SFML/Graphics.hpp>
#include <string>
#include "IMenuItem.h"
#include "TextItem.h"
#include "GameState.h"
#include "App.h"

namespace gui
{
	class Text : public IMenuItem, public TextItem
	{
	public:
		std::string text;
		Text(sf::Text text);//Label(int x, int y, int width, int height, std::function<GameState*(App&)> &clickEvent, std::string text);
		~Text();
		virtual GameState *EventUpdate(App& app, const sf::Event& event, GameUtility* gameUtility);
		virtual void Draw(App &app);
	};
}

#endif*/