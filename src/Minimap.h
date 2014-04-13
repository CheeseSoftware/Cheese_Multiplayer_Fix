#pragma once
//#ifdef X_X
#ifdef CLIENT
#include <SFML\Graphics.hpp>
#include "Selectable.h"
#include "Camera.h"

namespace gui
{
	class Minimap
		: Selectable
	{
		int viewWidth;
		int viewHeight;
		long cX;
		long cY;
		//sf::Image *map;
		sf::Texture texture;
		sf::Sprite sprite;

		sf::Uint8* pixels;
	public:
		Minimap(int x, int y, int witdh, int heigh);
		void Update(App &app, Game *game, GameUtility *gameUtility);
		void Draw(App &app, float drawAreax, float drawAreay, int drawAreaWidth, int drawAreaHeight);
	};
}
//#endif
#endif