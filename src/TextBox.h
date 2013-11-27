#ifndef _SERVER
#pragma once
#include "Label.h"

namespace gui
{
	class TextBox : public Label
	{
	public:
		TextBox(int x, int y, int width, int height, sf::String *text, sf::Font *font, int lineLength, int maxLength);
		~TextBox(void);
		virtual GameState *EventUpdate(App& app, const sf::Event& event, GameState* gameState, float x, float y);
	};
}
#endif

