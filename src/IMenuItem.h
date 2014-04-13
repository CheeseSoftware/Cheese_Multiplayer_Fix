#ifdef CLIENT
#pragma once
#include <SFML\Window.hpp>
class App;
class GameState;
class GameUtility;
class Game;

namespace gui
{
	class IMenuItem
	{
	public:
		virtual GameState *EventUpdate(App &app, const sf::Event &event, float x, float y)=0;
		virtual GameState *Update(App &app, Game *game)=0;
		virtual void Draw(App &app, float drawAreax, float drawAreay, int drawAreaWidth, int drawAreaHeight)=0;
	};
}
#endif