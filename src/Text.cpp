#ifdef MENUIDIOTI
#ifndef _SERVER
#include <SFML\Graphics.hpp>
#include "IMenuItem.h"
#include "Text.h"
#include "GameState.h"

namespace gui
{
	Text::Text(sf::Text *text) : TextItem(text)
	{

	}


	Text::~Text()
	{

	}

	GameState *Text::EventUpdate(App& app, const sf::Event& event, GameState* gameState)
	{
		return nullptr;
	}
}
#endif
#endif