#ifndef _SERVER
#include "TextBox.h"
#include <iostream>

namespace gui
{
	TextBox::TextBox(int x, int y, int width, int height, sf::String *text, sf::Font *font, int lineLength, int maxLength)
		: Label(x, y, width, height, text, font, lineLength, maxLength)
	{

	}


	TextBox::~TextBox(void)
	{
	}

	GameState *TextBox::EventUpdate(App& app, const sf::Event& event, GameState* gameState, float x, float y)
	{
		Label::EventUpdate(app, event, gameState, x, y);
		if(getSelected())
		{
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode < 128)
				{
					//std::cout << event.text.unicode << std::endl;
					switch(event.text.unicode)
					{
					case 8: //Backspace
						{
							sf::String temp = getText()->getString();
							if(temp.getSize() > 0)
							{
								temp.erase(temp.getSize() - 1);
								getText()->setString(temp);
							}
						}
						break;
					default:
						{
							if(getText()->getGlobalBounds().width < m_width)
								getText()->setString(getText()->getString() + event.text.unicode);
						}
						break;
					}
				}
			}
		}
		return nullptr;
	}
}
#endif
