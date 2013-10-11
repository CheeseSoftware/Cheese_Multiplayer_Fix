#ifdef MENUIDIOTI
#include "TextInputItem.h"
#include "PositionItem.h"

namespace gui
{
	GameState *TextInputItem::EventUpdate(App& app, const sf::Event& event, GameState* gameState)
	{
		if (event.type == sf::Event::TextEntered)
		{
			text.setString(text.getString() + event.text.unicode);
		}

		return TextItem::EventUpdate(app, event, gameState);
	}
}
#endif