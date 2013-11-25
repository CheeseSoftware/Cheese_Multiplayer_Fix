#ifdef MENUIDIOTI
#pragma once
#ifndef _SERVER

#include "IMenuItem.h"

namespace sf { class Text; }

namespace gui
{
	class TextItem : public IMenuItem
	{
	protected:
		sf::Text *text;
	public:
		TextItem(sf::Text *text);
		virtual GameState *EventUpdate(App &app, const sf::Event &event, GameState *gameState);
		virtual void Draw(App &app, int x, int y) const;
	};
}
#endif
#endif