#pragma once
#ifdef MENUIDIOTI
#ifndef _SERVER

#include <functional>
#include "App.h"
#include "IMenuItem.h"
#include "Selectable.h"

class GameUtility;
class GameState;

namespace gui
{
	class PositionItem : public virtual Selectable
	{
	protected:
		int x;
		int y;
		int width;
		int height;

	public:
		PositionItem(int x, int y, int width, int height, std::function<GameState*(App&)> &clickEvent);
		~PositionItem();

		virtual GameState *EventUpdate(App& app, const sf::Event& event, GameUtility* gameUtility);
		//virtual void OnClick(App&, const sf::Event&, GameUtility*);
		//virtual GameState *Update(App &app);
		virtual void OnLeftClick(App &app,GameUtility *gameUtility, const sf::Event &event);
		virtual void OnRightClick(App &app, GameUtility *gameUtility, const sf::Event &event);

		virtual void Draw(App &app);
		virtual void Draw(App &app, int x, int y)=0;
	};
}

#endif // !_SERVER*/*/
#endif