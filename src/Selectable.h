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

		std::function<GameState*(App&, GameState *gameState, const sf::Event)> onClickEvent;

		Selectable(std::function<GameState*(App&, GameState *gameState, const sf::Event)> onClickEvent);
	public:
		virtual bool getSelected();
		virtual GameState *EventUpdate(App& app, const sf::Event& event, GameState* gameState);
		virtual void OnLeftClick(App &app, GameState *gameState, const sf::Event &event);
		virtual void OnRightClick(App &app, GameState *gameState, const sf::Event &event);
		void Unselect();
	};
}
#endif