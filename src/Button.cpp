#ifdef CLIENT
#include "Button.h"
#include <iostream>
#include "App.h"

namespace gui
{
	Button::Button(int x, int y, sf::Sprite *texture, sf::String *text, sf::Font *font, int lineLength, int maxLength)
		: Label(x, y, texture, text, font, lineLength, maxLength)
	{
	}


	Button::~Button(void)
	{
	}

	void Button::Draw(App &app, float drawAreax, float drawAreay, int drawAreaWidth, int drawAreaHeight)
	{
		Label::Draw(app, drawAreax, drawAreay, drawAreaWidth, drawAreaHeight);
	}
}
#endif
