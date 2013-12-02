#pragma once
//#ifdef X_X
#ifndef _SERVER
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
		sf::Image *map;
		sf::Sprite sprite;
	public:
		Minimap(int x, int y, int witdh, int heigh);
		void Update(App &app, GameUtility *gameUtility);
		void Draw(App &app, float drawAreax, float drawAreay, int drawAreaWidth, int drawAreaHeight);
	};
}
//#endif
#endif