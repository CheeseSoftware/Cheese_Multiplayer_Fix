#ifdef CLIENT
#include "Selectable.h"
#include <iostream>
#include "GameState.h"
#include "App.h"

namespace gui
{
	Selectable::Selectable(int x, int y, sf::Sprite* texture)
		: down(false)
	{
		m_localX = x;
		m_localY = y;
		m_positionType = TopLeft;
		m_widthOffset = 0;
		m_heightOffset = 0;
		m_width = 10;   //Do not render invisible if some idiot forgot to give texture to constructor
		m_height = 10;  //Do not render invisible if some idiot forgot to give texture to constructor
		m_texture = texture;

		if(texture != nullptr)
		{
			m_width = texture->getTexture()->getSize().x;
			m_height = texture->getTexture()->getSize().y;
		}
	}

	Selectable::Selectable(int x, int y, int width, int height)
		: down(false)
	{
		m_localX = x;
		m_localY = y;
		m_positionType = TopLeft;
		m_widthOffset = 0;
		m_heightOffset = 0;
		m_width = width;
		m_height = height;
		m_texture = nullptr;
	}

	int Selectable::m_X(App &app)
	{
		int x = m_localX;

		if (m_positionType == PositionType::centerTop || m_positionType == PositionType::middleCenter || m_positionType == PositionType::centerDown)
		{
			x += app.getSize().x/2 - m_width/2;
		}
		else if (m_positionType == PositionType::TopRight || m_positionType == PositionType::centerRight || m_positionType == PositionType::DownRight)
		{
			x += app.getSize().x - m_width/2;
		}
		return x;
	}

	int Selectable::m_Y(App &app)
	{
		int y = m_localY;

		if (m_positionType == PositionType::centerLeft || m_positionType == PositionType::middleCenter || m_positionType == PositionType::centerRight)
		{
			y += app.getSize().y/2 - m_height/2;
		}
		else if (m_positionType == PositionType::DownLeft || m_positionType == PositionType::centerDown || m_positionType == PositionType::DownRight)
		{
			y += app.getSize().y - m_height/2;
		}
		return y;
	}

	int Selectable::RightX(App &app)
	{
		return m_X(app) + m_width;
	}

	int Selectable::BottomY(App &app)
	{
		return m_Y(app) + m_height;
	}


	bool Selectable::getSelected()
	{
		return selected;
	}

	GameState *Selectable::EventUpdate(App& app, const sf::Event& event, float x, float y)
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			sf::Vector2i mouse = sf::Mouse::getPosition(app);
			int x = m_X(app);
			int y = m_Y(app);
			int xx = RightX(app);
			int yy = BottomY(app);


			if (sf::Mouse::getPosition(app).x >= m_X(app) &&
				sf::Mouse::getPosition(app).x <= RightX(app) &&
				sf::Mouse::getPosition(app).y >= m_Y(app) &&
				sf::Mouse::getPosition(app).y <= BottomY(app))
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
			if (sf::Mouse::getPosition(app).x >= m_X(app) &&
				sf::Mouse::getPosition(app).x <= RightX(app) &&
				sf::Mouse::getPosition(app).y >= m_Y(app) &&
				sf::Mouse::getPosition(app).y <= BottomY(app))
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
			else if(this->getSelected())
				Unselect();
		}

		return nullptr;
	}

	GameState *Selectable::Update(App &app, Game *game)
	{
		return nullptr;
	}

	void Selectable::Draw(App &app, float drawAreax, float drawAreay, int drawAreaWidth, int drawAreaHeight)
	{
		//m_widthOffset = getPositionOffset(drawAreax, drawAreay, drawAreaWidth, drawAreaHeight).x;
		//m_heightOffset = getPositionOffset(drawAreax, drawAreay, drawAreaWidth, drawAreaHeight).y;
		if(m_texture != nullptr)
		{
			sf::Sprite sprite = sf::Sprite(*m_texture);
			sprite.setPosition(m_X(app), m_Y(app));
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