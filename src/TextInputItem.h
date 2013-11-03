#ifdef MENUIDIOTI
#ifndef _SERVER
#pragma once
#include "TextItem.h"

namespace gui
{
	class TextInputItem : public virtual TextItem
	{
		virtual GameState *EventUpdate(App& app, const sf::Event& event, GameState* gameState);
	};
}
#endif
#endif