#ifdef CLIENT
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
		/*sf::RectangleShape rectangle(sf::Vector2f(m_X(app), m_Y(app)));

		rectangle.setPosition(sf::Vector2f(m_X(app), m_Y(app)));

		// change the size to 100x100
		rectangle.setSize(sf::Vector2f(m_width, m_height));

		rectangle.setFillColor(sf::Color(64, 64, 64, 192));
		rectangle.setOutlineColor(sf::Color(192, 192, 192, 255));

		app.draw(rectangle);
		*/
		getText()->setPosition(m_X(app), m_Y(app));
		app.draw(*getText());
	}
}
#endif
