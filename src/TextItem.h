/*#pragma once
#ifndef _SERVER

#include "IMenuItem.h"

namespace sf { class Text; }

namespace gui
{
	class TextItem : public virtual IMenuItem
	{
	public:
		sf::Text text;
		TextItem(sf::Text text);
		virtual void Draw(App &app, int x, int y);
	};
}
#endif*/