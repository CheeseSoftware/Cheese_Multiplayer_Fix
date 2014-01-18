/*		int width;
		int height;
		long x;
		long y;
		sf::Texture map;
		Camera *camera;
*/
	//public:

#ifndef _SERVER

#include <functional>
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
		//map = new sf::Image();
		//map->create(viewWidth, viewHeight, sf::Color::Black);
		pixels = new sf::Uint8[width * height * 4];

		for (int i = 0; i < 4; i++)
		{
			for (int x = 0; x < width; x++)
			{
				for (int y = 0; y < height; y++)
					pixels[y*width*4 + x*4 + i] = 0;
			}
		}
		texture.create(width, height);
		texture.update(pixels);
		sprite.setTexture(texture);
	}

	void Minimap::Update(App &app, GameUtility *const gameUtility)
	{
		long playerX = (long)floor(gameUtility->getCamera().getEntityPosition().x/16+0.5)-viewWidth/2;
		long playerY = (long)floor(gameUtility->getCamera().getEntityPosition().y/16+0.5)-viewHeight/2;

		long deltaX = playerX - cX;
		long deltaY = playerY - cY;

		std::function<void()> yLoop;
		std::function<void(int y)> xLoop;
		std::function<void(int x, int y)> work;

		work = [&](int x, int y)
		{
			for (int i = 0; i < 4; i++)
				pixels[4*x + 4*viewWidth*y+i] = pixels[4*(x+deltaX) + 4*viewWidth*(y+deltaY)+i];
		};

		if (deltaX >= 0)
			xLoop = [&](int y)
			{
				for (int x = 0; x < viewWidth-deltaX; x++)
					work(x, y);
			};
		else
			xLoop = [&](int y)
			{
				for (int x = viewWidth- 1; x >= -deltaX; x--)
					work(x, y);
			};

		if (deltaY >= 0)
			yLoop = [&]()
			{
				for (int y = 0; y < viewHeight-deltaY; y++)
					xLoop(y);
			};
		else
			yLoop = [&]()
			{
				for (int y = viewHeight - 1; y >= -deltaY; y--)
					xLoop(y);
			};

		yLoop();

		/*sf::Image *image = new sf::Image();
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
		map = image;*/

		
		//map = new sf::Image();
		//map->create(viewWidth, viewHeight);//image;
		for (int i = 0; i < 4; i++)
		{
			for(int xx = 0; xx < viewWidth; xx++)
			{
				for(int yy = 0; yy < viewHeight; yy++)
				{
					if (deltaX + xx <= 0 ||
						deltaY + yy <= 0 ||
						deltaX + xx >= viewWidth || 
						deltaY + yy >= viewHeight)

						pixels[4*xx + 4*viewWidth*yy+i] = (gameUtility->getCurrentWorld()->getBlock(cX + xx, cY + yy, 2) == nullptr) ? 127:255;
				}
			}
		}

		texture.update(pixels);
		sf::Texture *texture2 = new sf::Texture();
		texture2->create(m_width, viewHeight);
		texture2->update(pixels);
		//sf::Texture *texture = new sf::Texture();
		//texture->loadFromImage(*map);

		sprite.setTexture(*texture2);

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