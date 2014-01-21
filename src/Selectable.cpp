#ifdef CLIENT
#include "Selectable.h"
#include "GameState.h"
#include <iostream>

namespace gui
{
	Selectable::Selectable(int x, int y, int width, int height)
		: down(false)
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
					OnLMBPressed(app, event, x, y);
				}
				else if(event.key.code == sf::Mouse::Right)
				{
					OnRMBPressed(app, event, x, y);
				}
			}
			else
				Unselect();
		}
		else if (event.type == sf::Event::MouseButtonReleased)
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
					OnLMBReleased(app, event, x, y);
					down = false;
				}
				else if(event.key.code == sf::Mouse::Right)
				{
					OnRMBReleased(app, event, x, y);
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


	void Selectable::OnLMBPressed(App &app, const sf::Event &event, float x, float y)
	{
		if(selected)
			Unselect();
		else
			selected = true;

		if (onLMBPressedFunction)
			onLMBPressedFunction(app, event, x, y);

		down = true;
	}

	void Selectable::OnLMBReleased(App &app, const sf::Event &event, float x, float y)
	{
		if(selected)
			Unselect();
		else
			selected = true;

		if (onLMBPressedFunction)
			onLMBPressedFunction(app, event, x, y);

		if (down)
			OnLMBClick(app, event, x, y);

		down = false;
	}

	void Selectable::OnLMBClick(App &app, const sf::Event &event, float x, float y)
	{
		if (onLMBClickFunction)
			onLMBClickFunction(app, event, x, y);
	}

	void Selectable::OnRMBPressed(App &app, const sf::Event &event, float x, float y)
	{
		if(selected)
			Unselect();
		else
			selected = true;

		if (onRMBPressedFunction)
			onRMBPressedFunction(app, event, x, y);
	}

		void Selectable::OnRMBReleased(App &app, const sf::Event &event, float x, float y)
	{
		/*if(selected)
			Unselect();
		else
			selected = true;*/

		if (onRMBPressedFunction)
			onRMBPressedFunction(app, event, x, y);

		//if (down)
		//	OnLMBClick(app, event, x, y);
	}

	void Selectable::OnRMBClick(App &app, const sf::Event &event, float x, float y)
	{
		if (onRMBClickFunction)
			onRMBClickFunction(app, event, x, y);
	}

	void Selectable::OnHover(App &app, const sf::Event &event, float x, float y)
	{
		if (onHoverFunction)
			onHoverFunction(app, event, x, y);
	}

	void Selectable::OnHoverReleased(App &app, const sf::Event &event, float x, float y)
	{

	}

	sf::Vector2f Selectable::getSize()
	{
		return sf::Vector2f(m_width, m_height); 
	}

	void Selectable::Unselect()
	{
		selected = false;
		down = false;
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