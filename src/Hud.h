#ifndef _SERVER
#pragma once
#include "Selectable.h"

namespace gui
{
	class Hud : Selectable
	{
	private:
		std::vector<Selectable*> hudItems;
	public:
		Hud(void);
		~Hud(void);
		virtual GameState *EventUpdate(App &app, const sf::Event &event, GameState *gameState);
		virtual GameState *Update(App &app);
		virtual void Draw(App &app, float x, float y);
		void AddItem(Selectable *item);
		void RemoveItem(size_t i);
	};
}
#endif

