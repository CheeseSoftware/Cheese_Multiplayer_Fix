#ifndef _SERVER
#include <SFML\Graphics.hpp>
#include "App.h"
#include "IMenuItem.h"
#include "GameState.h"
#include "MenuItemContainer.h"
#include <iostream>

namespace gui
{
	MenuItemContainer::MenuItemContainer(int x, int y, int width, int height)
		: Selectable(x, y, width, height)
	{
		itemList = new std::vector<Selectable*>();
	}

	GameState *MenuItemContainer::EventUpdate(App &app, const sf::Event &event, GameUtility* gameUtility, float x, float y)
	{
		//TEMPORÄRT XD //eventHandler.EventUpdate(app, event, gamestate);
		//std::cout << "eventupdating menuitemcontainer X:" << x << " Y:" << y << std::endl;
		Selectable::EventUpdate(app, event, gameUtility, x, y);
		for (Selectable *item : *itemList)
		{
			item->EventUpdate(app, event, gameUtility, x + getPosition().x + m_widthOffset, y + getPosition().y + m_heightOffset);
			//std::cout << "eventupdating selectable X:" << x + getPosition().x + m_widthOffset << " Y:" << y + getPosition().y + m_heightOffset << std::endl;
		}
		return nullptr;
	}

	GameState *MenuItemContainer::Update(App &app)
	{
		for (Selectable *item : *itemList)
			item->Update(app);
		return nullptr;
	}

	void MenuItemContainer::Draw(App &app, float drawAreax, float drawAreay, int drawAreaWidth, int drawAreaHeight)
	{
		Selectable::Draw(app, drawAreax, drawAreay, drawAreaWidth, drawAreaHeight);
		for (Selectable *i : *itemList)
		{
			i->Draw(app,
				m_x + m_widthOffset + drawAreax,
				m_y + m_heightOffset + drawAreay, 
			drawAreaWidth < m_width ? drawAreaWidth : m_width, drawAreaHeight < m_height ? drawAreaHeight : m_height);
		}
	}

	sf::Vector2f MenuItemContainer::getSize()
	{
		sf::Vector2f output = sf::Vector2f(0, 0);
		for (Selectable *item : *itemList)
		{
			if(item->getSize().x + item->getPosition().x > output.x)
				output.x = item->getSize().x + item->getPosition().x;
			if(item->getSize().y + item->getPosition().y > output.y)
				output.y = item->getSize().y + item->getPosition().y;
		}
		return output;
	}

	void MenuItemContainer::Add(Selectable *item)
	{
		itemList->push_back(item);
	}

	void MenuItemContainer::Remove(size_t i)
	{
		itemList->erase(itemList->begin() + i);
	}

}
#endif