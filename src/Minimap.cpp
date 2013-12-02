/*		int width;
		int height;
		long x;
		long y;
		sf::Texture map;
		Camera *camera;
*/
	//public:

#ifndef _SERVER

#include <math.h>
#include <SFML\Graphics.hpp>

#include "Minimap.h"
#include "Camera.h"
#include "GameUtility.h"

namespace gui
{
	Minimap::Minimap(int x, int y, int width, int height)
		: Selectable(x, y, width, height) 
	{
		cX = 0;
		cY = 0;
		viewWidth = width;
		viewHeight = height;
		map = new sf::Image();
		map->create(viewWidth, viewHeight, sf::Color::Black);
	}

	void Minimap::Update(App &app, GameUtility *const gameUtility)
	{
		long playerX = (long)floor(gameUtility->getCamera().getEntityPosition().x/16+0.5)-viewWidth/2;
		long playerY = (long)floor(gameUtility->getCamera().getEntityPosition().y/16+0.5)-viewHeight/2;

		long deltaX = playerX - cX;
		long deltaY = playerY - cY;

		sf::Image *image = new sf::Image();
		image->create(viewWidth, viewHeight, sf::Color::Black);
		image->copy(*map
			, (deltaX < 0)? -deltaX:0
			, (deltaY < 0)? -deltaY:0
			, sf::IntRect(//(0,0,viewWidth,viewHeight));
				  (deltaX > 0)? deltaX:0
				, (deltaY > 0)? deltaY:0
				, 0
				, 0));

		delete map;
		map = image;

		
		//map = new sf::Image();
		//map->create(viewWidth, viewHeight);//image;

		for(int xx = 0; xx < viewWidth; xx++)
		{
			for(int yy = 0; yy < viewHeight; yy++)
			{
				if (deltaX + xx < 0 ||
					deltaY + yy < 0 ||
					deltaX + xx > viewWidth || 
					deltaY + yy > viewHeight)

					map->setPixel(xx, yy, (gameUtility->getCurrentWorld()->getBlock(cX + xx, cY + yy, 2) == 0)? sf::Color::Black : sf::Color::White);
			}
		}
		
		sf::Texture *texture = new sf::Texture();
		texture->loadFromImage(*map);

		sprite.setTexture(*texture);

		cX = playerX;
		cY = playerY;
	}

	void Minimap::Draw(App &app, float drawAreax, float drawAreay, int drawAreaWidth, int drawAreaHeight)
	{
		sprite.setPosition(m_x, m_y);
		app.draw(sprite, sf::RenderStates::Default);
	}
}
#endif