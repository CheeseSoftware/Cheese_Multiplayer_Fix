#ifdef CLIENT
#include "Label.h"
#include <iostream>
#include "App.h"

namespace gui
{
	Label::Label(int x, int y, sf::Sprite *texture, sf::String *temptext, sf::Font *font, int lineLength, int maxLength)
		: Selectable(x, y, texture)
	{
		m_text = new sf::Text(*temptext, *font);
		m_text->setCharacterSize(24);
		m_text->setColor(sf::Color::Green);
		m_text->setStyle(sf::Text::Bold);
		m_lineLength = lineLength;
		m_maxLength = maxLength;
	}

	Label::~Label()
	{
	}

	void Label::Draw(App &app, float drawAreax, float drawAreay, int drawAreaWidth, int drawAreaHeight)
	{
		Selectable::Draw(app, drawAreax, drawAreay,  drawAreaWidth, drawAreaHeight);
		getText()->setPosition(m_X(app) + (m_width - getText()->getGlobalBounds().width)/2, m_Y(app) + (m_height - getText()->getGlobalBounds().height)/2 - 2); //centrera texten inuti labeln
		app.draw(*getText());
	}
}
#endif