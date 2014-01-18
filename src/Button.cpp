#ifndef _SERVER
#include "Button.h"
#include <iostream>

namespace gui
{
	Button::Button(int x, int y, int width, int height, sf::String *text, sf::Font *font, int lineLength, int maxLength, ClickFunction leftClick, ClickFunction rightClick)
		: Label(x, y, width, height, text, font, lineLength, maxLength)
	{
		onLeftClickFunction = leftClick;
		onRightClickFunction = rightClick;
	}


	Button::~Button(void)
	{
	}

	GameState *Button::EventUpdate(App& app, const sf::Event& event, GameUtility* gameUtility, float x, float y)
	{
<<<<<<< HEAD
		Selectable::EventUpdate(app, event, gameUtility, x, y);
=======
		Selectable::EventUpdate(app, event, x, y);
>>>>>>> c953a28c2ff85939864a8166e4b9475db0da2b73
		return nullptr;
	}

	void Button::Draw(App &app, float drawAreax, float drawAreay, int drawAreaWidth, int drawAreaHeight)
	{
		getText()->setPosition(m_x + m_widthOffset + drawAreax, m_y + m_heightOffset + drawAreay);
		app.draw(*getText());
	}

	void Button::OnLeftClick(App &app, const sf::Event &event, GameUtility* gameUtility, float x, float y)
	{
		onLeftClickFunction(app, event, gameUtility, x, y);
	}

	void Button::OnRightClick(App &app, const sf::Event &event, GameUtility* gameUtility, float x, float y)
	{
		onRightClickFunction(app, event, gameUtility, x, y);
	}
}
#endif
