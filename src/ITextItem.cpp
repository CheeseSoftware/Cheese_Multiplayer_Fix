#ifndef _SERVER
#include "ITextItem.h"
#include <SFML\Graphics.hpp>

ITextItem::ITextItem(sf::Text)
{
	this->text = text;
	text.setPosition(x + 1, y + height - text.getCharacterSize()<<1);
}

void ITextItem::Draw(App &app)
{
	app.draw(text);
}
#endif