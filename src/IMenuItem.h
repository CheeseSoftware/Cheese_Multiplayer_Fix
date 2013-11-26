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
		virtual GameState *EventUpdate(App &app, const sf::Event &event, GameState *gameState)=0;
		virtual GameState *Update(App &app)=0;
		virtual void Draw(App &app, float x, float y)=0;
	};
}
#endif