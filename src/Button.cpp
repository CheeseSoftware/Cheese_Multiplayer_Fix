#ifdef CLIENT
#include "Button.h"
#include <iostream>
#include "App.h"

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
		getText()->setPosition(m_X(app), m_Y(app));
		app.draw(*getText());
	}
}
#endif
