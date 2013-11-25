#ifndef _SERVER
#pragma once
class App;
class GameState;
namespace sf { class Event; }

namespace gui
{
	class GraphicalContainer
	{
	public:
		GraphicalContainer(int x, int y, int width, int height);
		virtual void EventUpdate(App &app, const sf::Event &event, GameState *gamestate)=0;
		virtual GameState *Update(App &app)=0;
		virtual void Draw(App &app)=0;
		int m_x;
		int m_y;
		int m_width;
		int m_height;
	};
}
#endif