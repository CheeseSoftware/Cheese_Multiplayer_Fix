#ifndef _SERVER
#pragma once
//#ifdef MENUIDIOTI
#include <functional>
#include "IMenuItem.h"
#include "App.h"

namespace gui
{
	//typedef std::function<GameState*(App&, const sf::Event&, GameState *gameState)> ClickEvent;

	class Selectable : public virtual IMenuItem
	{
	protected:
		bool selected;
		bool down;
		bool clicked;
		int m_x;
		int m_y;
		//ClickEvent onLeftClickEvent;
		//ClickEvent onRightClickEvent;

		Selectable(int x, int y/*ClickEvent leftClickEvent, ClickEvent rightClickEvent*/);
	public:
		virtual bool getSelected();
		virtual GameState *EventUpdate(App& app, const sf::Event& event, GameState* gameState);
		virtual GameState *Update(App &app);
		virtual void Draw(App &app, float x, float y);
		virtual void OnLeftClick(App &app, const sf::Event &event, GameState *gameState);
		virtual void OnRightClick(App &app, const sf::Event &event, GameState *gameState);
		sf::Vector2f getPosition() { return sf::Vector2f(m_x, m_y); }
		//sf::Vector2f getSize() { return sf::Vector2f(sizeX, sizeY); }
		void Unselect();
	};
}
#endif