#ifndef _SERVER
#include "Button.h"
#include <iostream>

namespace gui
{
	Button::Button(int x, int y, int width, int height, sf::String *text, sf::Font *font, int lineLength, int maxLength)
		: Label(x, y, width, height, text, font, lineLength, maxLength)
	{
	}


	Button::~Button(void)
	{
	}

	void Button::Draw(App &app, float drawAreax, float drawAreay, int drawAreaWidth, int drawAreaHeight)
	{
		// define a 120x50 rectangle
		sf::RectangleShape rectangle(sf::Vector2f(m_x + m_widthOffset + drawAreax, m_y + m_heightOffset + drawAreay));

		// change the size to 100x100
		rectangle.setSize(sf::Vector2f(m_width, m_height));

		app.draw(rectangle);

		getText()->setPosition(m_x + m_widthOffset + drawAreax, m_y + m_heightOffset + drawAreay);
		app.draw(*getText());
	}
}
#endif
