#ifdef MENUIDIOTI
#include "TextItem.h"

namespace gui
{
	class TextInputItem : public virtual TextItem
	{
		virtual GameState *EventUpdate(App& app, const sf::Event& event, GameUtility* gameUtility);
	};
}
#endif