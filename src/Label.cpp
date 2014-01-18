#ifndef _SERVER
#include "Label.h"
#include <iostream>

namespace gui
{
	Label::Label(int x, int y, int width, int height, sf::String *temptext, sf::Font *font, int lineLength, int maxLength)
		: Selectable(x, y, width, height)
	{
		m_text = new sf::Text(*temptext, *font);
		m_text->setCharacterSize(24);
		m_text->setColor(sf::Color::Green);
		m_text->setStyle(sf::Text::Bold);
		m_width = m_text->getGlobalBounds().width;
		m_height = m_text->getGlobalBounds().height;
		m_lineLength = lineLength;
		m_maxLength = maxLength;
		//delete temptext;
		//delete font;
	}

	Label::~Label()
	{
	}

	GameState *Label::EventUpdate(App& app, const sf::Event& event, float x, float y)
	{
		Selectable::EventUpdate(app, event, x, y);
		return nullptr;
	}

	void Label::Draw(App &app, float drawAreax, float drawAreay, int drawAreaWidth, int drawAreaHeight)
	{
		Selectable::Draw(app, drawAreax, drawAreay,  drawAreaWidth, drawAreaHeight);
		getText()->setPosition(m_x + m_widthOffset + drawAreax, m_y + m_heightOffset + drawAreay);
		app.draw(*getText());
	}

	void Label::OnLeftClick(App &app, const sf::Event &event, float x, float y)
	{
		Selectable::OnLeftClick(app, event, x, y);
	}

	void Label::OnRightClick(App &app, const sf::Event &event, float x, float y)
	{
		Selectable::OnRightClick(app, event, x, y);
	}
}
#endif