#ifndef _SERVER
#include "Label.h"

namespace gui
{
	Label::Label(int x, int y, int width, int height, sf::String *temptext, sf::Font *font)
		: Selectable(x, y, width, height)
	{
		text = new sf::Text(*temptext, *font);
		text->setCharacterSize(24);
		text->setColor(sf::Color::Green);
		text->setStyle(sf::Text::Bold);
		m_width = text->getGlobalBounds().width;
		m_height = text->getGlobalBounds().height;
	}

	Label::~Label()
	{
	}

	GameState *Label::EventUpdate(App& app, const sf::Event& event, GameState* gameState, float x, float y)
	{
		Selectable::EventUpdate(app, event, gameState, x, y);
		return nullptr;
	}

	void Label::Draw(App &app, float drawAreax, float drawAreay, int drawAreaWidth, int drawAreaHeight)
	{
		text->setPosition(m_x + getPositionOffset(drawAreax, drawAreay, drawAreaWidth, drawAreaHeight).x, m_y + getPositionOffset(drawAreax, drawAreay, drawAreaWidth, drawAreaHeight).y);
		app.draw(*text);
	}
}
#endif