#ifndef _SERVER
#include "Hud.h"

namespace gui
{
	Hud::Hud(void) : Selectable(0, 0)
	{
		hudItems = std::vector<Selectable*>();
	}


	Hud::~Hud(void)
	{
	}

	GameState *Hud::EventUpdate(App &app, const sf::Event &event, GameState *gameState)
	{
		return nullptr;
	}

	void Hud::Draw(App &app, float x, float y)
	{
		for(Selectable* item : hudItems)
			item->Draw(app, item->getPosition().x, item->getPosition().y);
	}

	void Hud::AddItem(Selectable *item)
	{
		hudItems.push_back(item);
	}

	void Hud::RemoveItem(size_t i)
	{
		hudItems.erase(hudItems.begin() + i);
	}
}
#endif