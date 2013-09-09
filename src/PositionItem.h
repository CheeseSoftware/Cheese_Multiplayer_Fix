/*#pragma once
#ifndef _SERVER

#ifndef MENUITEM_H_INCLUDED
#define MENUITEM_H_INCLUDED

#pragma once

#include <functional>
#include "App.h"
#include "IMenuItem.h"

class GameUtility;
class GameState;

namespace gui
{
	class PositionItem : public virtual IMenuItem
	{
	protected:
		int x;
		int y;
		int width;
		int height;
		bool selected;
		bool down;
		bool clicked;
		std::function<GameState*(App&)> clickEvent;

		PositionItem();
	public:
		PositionItem(int x, int y, int width, int height);
		~PositionItem();

		virtual bool getSelected();

		virtual GameState *EventUpdate(App& app, const sf::Event& event, GameUtility* gameUtility);
		//virtual void OnClick(App&, const sf::Event&, GameUtility*);
		//virtual GameState *Update(App &app);

		virtual void Draw(App &app);
		virtual void Draw(App &app, int x, int y)=0;
	};
}

#endif // MENUITEM_H_INCLUDED
#endif // !_SERVER*/