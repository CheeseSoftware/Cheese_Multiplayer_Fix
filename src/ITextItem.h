#include "MenuItem.h"

namespace sf { class Text; }

class ITextItem : virtual MenuItem
{
public:
	sf::Text text;
	ITextItem(sf::Text text);
	virtual void Draw(App &app);
};