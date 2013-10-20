#pragma once
#ifdef MENUIDIOTI
#include <functional>
#include "IMenuItem.h"


namespace gui
{
	class Selectable : public virtual IMenuItem
	{
	protected:
		bool selected;
		bool down;
		bool clicked;

		std::function<GameState*(App&, const sf::Event&, GameState *gameState)> onClickEvent;

		Selectable(std::function<GameState*(App&, const sf::Event&, GameState *gameState)> onClickEvent);
	public:
		virtual bool getSelected();
		virtual GameState *EventUpdate(App& app, const sf::Event& event, GameState* gameState);
		virtual void OnLeftClick(App &app, const sf::Event &event, GameState *gameState);
		virtual void OnRightClick(App &app, const sf::Event &event, GameState *gameState);
		void Unselect();
	};
}
#endif