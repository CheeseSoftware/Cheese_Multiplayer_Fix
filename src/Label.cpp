#ifndef _SERVER
#include "Label.h"
#include <iostream>

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
		text->setPosition(m_x + m_widthOffset + drawAreax, m_y + m_heightOffset + drawAreay);
		app.draw(*text);
	}

	void Label::OnLeftClick(App &app, const sf::Event &event, GameState *gameState, float x, float y)
	{
		std::cout << "a " << (std::string)this->text->getString() << " was clicked!" << std::endl;
	}

	void Label::OnRightClick(App &app, const sf::Event &event, GameState *gameState, float x, float y)
	{

	}
}
#endif