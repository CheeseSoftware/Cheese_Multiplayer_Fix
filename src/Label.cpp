/*#ifdef MENUIDIOTI
#include "Label.h"

namespace gui
{
	Label::Label(int x, int y, ClickEvent &clickEvent, sf::Text &text)
		:TextItem(text), PositionItem(x, y, 0, 0, clickEvent)//: PositionItem(x, y, 100, 12, clickEvent) , TextItem(text)
	{

	}

	void Label::OnLeftClick(App &app, const sf::Event &event, GameState *gameState)
	{
		selected = true;
	}

	void Label::OnRightClick(App &app, const sf::Event &event, GameState *gameState)
	{
		selected = true;
	}
}
#endif*/