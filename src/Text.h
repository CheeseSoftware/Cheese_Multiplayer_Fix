/*#ifndef _SERVER
#pragma once

#ifndef Label_H_INCLUDED
#define Label_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <string>
#include "TextItem.h"
#include "GameState.h"
#include "App.h"

namespace gui
{
	class Text : public IMenuItem, public TextItem
	{
	public:
		std::string text;
		Text(std::string text);//Label(int x, int y, int width, int height, std::function<GameState*(App&)> &clickEvent, std::string text);
		~Text();
		virtual GameState *EventUpdate(App& app, const sf::Event& event, GameUtility* gameUtility);
		virtual void Draw(App &app);
	};
}

#endif
#endif*/