#ifdef MENUIDIOTI
#include "TextItem.h"

gui::TextItem::TextItem(sf::Text *text)
{
	this->text = text;
}

void gui::TextItem::Draw(App &app, int x, int y) const
{
	text->setPosition(x, y);
	app.draw(*text, sf::RenderStates::Default);
}

GameState *gui::TextItem::EventUpdate(App &app, const sf::Event &event, GameState *gameState)
{
	return gameState;
}
#endif