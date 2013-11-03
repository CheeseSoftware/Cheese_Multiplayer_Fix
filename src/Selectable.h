#pragma once
#ifdef MENUIDIOTI
#include <functional>
#include "IMenuItem.h"


namespace gui
{
	typedef std::function<GameState*(App&, const sf::Event&, GameState *gameState)> ClickEvent;

	class Selectable : public virtual IMenuItem
	{
	protected:
		bool selected;
		bool down;
		bool clicked;

		ClickEvent onClickEvent;

		Selectable(ClickEvent clickEvent);
	public:
		virtual bool getSelected();
		virtual GameState *EventUpdate(App& app, const sf::Event& event, GameState* gameState);
		virtual void OnLeftClick(App &app, const sf::Event &event, GameState *gameState);
		virtual void OnRightClick(App &app, const sf::Event &event, GameState *gameState);
		void Unselect();
	};
}
#endif