#ifndef _SERVER
#pragma once
#include "Label.h"

namespace gui
{
	class Button : Label
	{
	public:
		Button(int x, int y, int width, int height, sf::String *text, sf::Font *font);
		~Button(void);
	};
}
#endif

