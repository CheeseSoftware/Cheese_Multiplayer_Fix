#ifndef _SERVER
#include "Button.h"

namespace gui
{
	Button::Button(int x, int y, int width, int height, sf::String *text, sf::Font *font)
		: Label(x, y, width, height, text, font)
	{
	}


	Button::~Button(void)
	{
	}
}
#endif
