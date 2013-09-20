#ifdef MENUIDIOTI
#ifndef _SERVER
#include <SFML/Graphics.hpp>
#include "PositionItem.h"
#include "GameState.h"
#include "App.h"

namespace gui
{
	PositionItem::PositionItem()
	{
	 
	}

	PositionItem::PositionItem(int x, int y, int width, int height, std::function<GameState*(App&)> &clickEvent)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		selected = false;
		down = false;
		clicked = false;
	}

	PositionItem::~PositionItem()
	{

	}

	GameState *PositionItem::EventUpdate(App& app, const sf::Event& event, GameUtility* gameUtility)
	{
		if (event.type == sf::Event::MouseMoved)
		{
			selected = (sf::Mouse::getPosition().x >= x && sf::Mouse::getPosition().x <= x+width && sf::Mouse::getPosition().y >= y && sf::Mouse::getPosition().y <= y+height);
		}
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.key.code == sf::Mouse::Left && selected)
			{
				down = true;
				selected = true;
			}
		}
		else if (event.type == sf::Event::MouseButtonReleased)
		{
			if (event.key.code == sf::Mouse::Left)
			{
				if (down)
				{
					clicked = true;
					OnLeftClick(app, gameUtility, event);
					down = false;
				}
			}
		}

		return nullptr;
	}

	void PositionItem::OnLeftClick(App &app, GameUtility *gameUtility)
	{
		selected = true;
	}

	virtual void OnRightClick(App &app, GameUtility *gameUtility)
	{
		selected = true;
	}

	void PositionItem::Draw(App &app)
	{
		Draw(app, x, y);
	}
	/*GameState *PositionItem::Update(App &app)
	{
		if (clicked && selected && clickEvent != 0)
				return clickEvent(app);

		clicked = false;
		return 0;
	}*/
}
#endif // !_SERVER
#endif