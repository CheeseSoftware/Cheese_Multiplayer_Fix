#ifdef MENUIDIOTI
#include "Selectable.h"
#include "GameState.h"
#include <iostream>

namespace gui
{
	Selectable::Selectable(int x, int y, int width, int height)
	{
		m_x = x;
		m_y = y;
		m_width = width;
		m_height = height;
		m_positionType = TopLeft;
		m_widthOffset = 0;
		m_heightOffset = 0;
		m_texture = nullptr;
	}

	bool Selectable::getSelected()
	{
		return selected;
	}

	GameState *Selectable::EventUpdate(App& app, const sf::Event& event, float x, float y)
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			//std::cout << "posx:" << x + getPosition().x + m_widthOffset << " posy:" << y + getPosition().y + m_heightOffset << std::endl;
			//std::cout << "mousex:" << sf::Mouse::getPosition().x << " mousey: " << sf::Mouse::getPosition().y << std::endl;
			if (sf::Mouse::getPosition(app).x >= x + getPosition().x + m_widthOffset &&
				sf::Mouse::getPosition(app).x <= x + getPosition().x + m_widthOffset + getSize().x &&
				sf::Mouse::getPosition(app).y >= y + getPosition().y + m_heightOffset &&
				sf::Mouse::getPosition(app).y <= y + getPosition().y + m_heightOffset + getSize().y)
			{
				if(event.key.code == sf::Mouse::Left)
				{
					OnLeftClick(app, event, x, y);
				}
				else if(event.key.code == sf::Mouse::Right)
				{
					OnRightClick(app, event, x, y);
				}
			}
			else
				Unselect();
		}

		return nullptr;
	}

	GameState *Selectable::Update(App &app, Game &game)
	{
		return nullptr;
	}

	void Selectable::Draw(App &app, float drawAreax, float drawAreay, int drawAreaWidth, int drawAreaHeight)
	{
		m_widthOffset = getPositionOffset(drawAreax, drawAreay, drawAreaWidth, drawAreaHeight).x;
		m_heightOffset = getPositionOffset(drawAreax, drawAreay, drawAreaWidth, drawAreaHeight).y;
		if(m_texture != nullptr)
		{
			sf::Sprite sprite = sf::Sprite(*m_texture);
			sprite.setPosition(m_x + m_widthOffset + drawAreax, m_y + m_heightOffset + drawAreay);
			app.draw(sprite);
		}
	}

	void Selectable::OnLeftClick(App &app, const sf::Event &event, float x, float y)
	{
		if(selected)
			Unselect();
		else
			selected = true;
	}

	void Selectable::OnRightClick(App &app, const sf::Event &event, float x, float y)
	{
		if(selected)
			Unselect();
		else
			selected = true;
	}

	sf::Vector2f Selectable::getSize()
	{
		return sf::Vector2f(m_width, m_height); 
	}

	void Selectable::Unselect()
	{
		selected = false;
	}

	sf::Vector2f Selectable::getPositionOffset(float drawAreax, float drawAreay, int drawAreaWidth, int drawAreaHeight)
	{
		sf::Vector2f output = sf::Vector2f(0, 0);
		switch(m_positionType)
		{
		case TopRight:
			output.x += (drawAreaWidth - getSize().x);
			break;
		case DownLeft:
			output.y += (drawAreaHeight - getSize().y);
			break;
		case DownRight:
			output.x += (drawAreaWidth - getSize().x);
			output.y += (drawAreaHeight - getSize().y);
			break;
		case centerLeft:
			output.y += drawAreaHeight / 2 - getSize().y / 2;
			break;
		case centerRight:
			output.x += (drawAreaWidth - getSize().x);
			output.y += drawAreaHeight / 2 - getSize().y / 2;
			break;
		case middleCenter:
			output.x += drawAreaWidth / 2 - getSize().x / 2;
			output.y += drawAreaHeight / 2 - getSize().y / 2;
			break;
		case centerTop:
			output.x += drawAreaWidth / 2 - getSize().x / 2;
			break;
		case centerDown:
			output.x += drawAreaWidth / 2 - getSize().x / 2;
			output.y += (drawAreaHeight - getSize().y);
			break;
		}
		return output;
	}

	void Selectable::setPositionType(PositionType positionType)
	{
		m_positionType = positionType;
	}
}
#endif