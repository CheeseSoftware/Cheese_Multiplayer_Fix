#pragma once
#ifdef MENUIDIOTI

#include "App.h"
//#include "GameUtility.h"
//#include "GameState.h"

class GameState;
class GameUtility;

namespace gui
{
	class IMenuItem
	{
	public:
		virtual bool getSelected()=0;

		virtual GameState *EventUpdate(App &app, const sf::Event &event, GameUtility *gameUtility)=0;
		virtual void OnLeftClick(App &app,GameUtility *gameUtility, const sf::Event &event)=0; // >.< gameUtility ska ersättas med menuUtility eller något
		virtual void OnRightClick(App &app,GameUtility *GameUtility, const sf::Event &event)=0;
		virtual void Draw(App &app, int x, int y)=0;
	};
}
#endif