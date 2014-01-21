#pragma once
#ifdef CLIENT
#include "App.h"
#include "MainCallbacks.h"
class GameState;
class GameUtility;

namespace gui
{
	class IMenuItem
	{
	public:
		virtual GameState *EventUpdate(App &app, const sf::Event &event, float x, float y)=0;
		virtual GameState *Update(App &app, Game &game)=0;
		virtual void Draw(App &app, float drawAreax, float drawAreay, int drawAreaWidth, int drawAreaHeight)=0;
	};
}
#endif