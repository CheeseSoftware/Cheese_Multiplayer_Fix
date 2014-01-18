#pragma once
#ifdef MENUIDIOTI

#include "App.h"
#include "MainCallbacks.h"
//#include "GameUtility.h"
//#include "GameState.h"

class GameState;
class GameUtility;

namespace gui
{
	class IMenuItem
	{
	public:
<<<<<<< HEAD
		virtual GameState *EventUpdate(App &app, const sf::Event &event, GameUtility* gameUtility, float x, float y)=0;
		virtual GameState *Update(App &app)=0;
=======
		virtual GameState *EventUpdate(App &app, const sf::Event &event, float x, float y)=0;
		virtual GameState *Update(App &app, Game &game)=0;
>>>>>>> c953a28c2ff85939864a8166e4b9475db0da2b73
		virtual void Draw(App &app, float drawAreax, float drawAreay, int drawAreaWidth, int drawAreaHeight)=0;
	};
}
#endif