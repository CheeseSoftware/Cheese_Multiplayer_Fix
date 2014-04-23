#ifdef CLIENT
#pragma once
#include "Label.h"


namespace gui
{
	class Button : public Label
	{
	public:
		Button(int x, int y, sf::Sprite *texture, sf::String *text, sf::Font *font, int lineLength, int maxLength);
		~Button(void);
		virtual void Draw(App &app, float drawAreax, float drawAreay, int drawAreaWidth, int drawAreaHeight);
	};
}
#endif

