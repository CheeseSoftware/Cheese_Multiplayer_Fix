#ifndef _SERVER
#include "Label.h"

namespace gui
{
	Label::Label(int x, int y, /*ClickEvent &clickEvent, */sf::String text, sf::Font font)
		: GUIItem(x, y, 0, 0), sf::Text(text, font)
	{

	}

	Label::~Label()
	{
	}

	GameState *Label::EventUpdate(App& app, const sf::Event& event, GameState* gameState)
	{
		return gameState;
	}

	void Label::Draw(App &app, float x, float y) const
	{
		//thissetPosition(sf::Vector2f(x, y));
		//app.draw(*this);
	}

	void Label::OnLeftClick(App &app, const sf::Event &event, GameState *gameState)
	{

	}

	void Label::OnRightClick(App &app, const sf::Event &event, GameState *gameState)
	{

	}
}
#endif