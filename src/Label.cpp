#ifndef _SERVER
#include "Label.h"

namespace gui
{
	Label::Label(int x, int y, /*ClickEvent &clickEvent, */sf::String *temptext, sf::Font *font)
		: Selectable(x, y)
	{
		text = new sf::Text(*temptext, *font);
		text->setCharacterSize(24);
		text->setColor(sf::Color::Green);
		text->setStyle(sf::Text::Bold);
	}

	Label::~Label()
	{
	}

	GameState *Label::EventUpdate(App& app, const sf::Event& event, GameState* gameState)
	{
		return gameState;
	}

	void Label::Draw(App &app, float x, float y)
	{
		text->setPosition(x, y);
		app.draw(*text);
	}

	void Label::OnLeftClick(App &app, const sf::Event &event, GameState *gameState)
	{

	}

	void Label::OnRightClick(App &app, const sf::Event &event, GameState *gameState)
	{

	}
}
#endif