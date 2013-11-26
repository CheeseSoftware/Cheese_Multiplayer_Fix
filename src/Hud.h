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
		virtual GameState *EventUpdate(App &app, const sf::Event &event, GameState *gameState)=0;
		virtual void Draw(App &app, float x, float y)=0;
		void AddItem(Selectable *item);
		void RemoveItem(size_t i);
	};
}
#endif

