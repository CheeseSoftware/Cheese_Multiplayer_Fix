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
		getText()->setPosition(m_x + m_widthOffset + drawAreax, m_y + m_heightOffset + drawAreay);
		app.draw(*getText());
	}
}
#endif
