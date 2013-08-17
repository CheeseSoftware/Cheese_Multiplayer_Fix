#ifndef _SERVER
#include "NoobishBlockMenu.h"
#include "World.h"
#include "Block.h"
#include "TextureContainer.h"
#include <SFML\Network.hpp>

NoobishBlockMenu::NoobishBlockMenu(World *world)
{
	selected = 0;
	blockMenu = new std::pair<Block*, unsigned short>*[2];
	for(int i = 0; i < 2; i++)
	{
		blockMenu[i] = new std::pair<Block*, unsigned short>[80];
		for(int x = 0; x < 80; x++)
		{
			if (x < 50)
				blockMenu[i][x] = std::pair<Block*, unsigned short>(world->getBlockType(1+i, x), x);
			else
				blockMenu[i][x] = std::pair<Block*, unsigned short>(world->getBlockType(3, x%4), x%4);
		}
	}
}

void NoobishBlockMenu::EventUpdate(App &app, const sf::Event &event, World *world)
{
	if(event.type == sf::Event::MouseButtonPressed)
	{
		if(event.key.code == sf::Mouse::Left)
		{
			if (event.mouseButton.y >= app.getSize().y-32)
			{
				std::cout << "den gamla storkossan är: " << selected << std::endl;
				//if (event.mouseButton.x <= 80*16)
				{
					int layer = (event.mouseButton.x >= app.getSize().y-16)? 1:0;
					selected = event.mouseButton.x>>4;
					std::cout << "den nya storkossan är: " << selected << std::endl;
				}
			}
			else
			{
				int x = (int)(app.getView().getCenter().x-app.getView().getSize().x/2 + 256 + event.mouseButton.x)>>4;
				int y = (int)(app.getView().getCenter().y-app.getView().getSize().y/2 + 256 + event.mouseButton.y)>>4;
				int layer = (selected >= 80)? 1:0;

				world->setBlockAndMetadata(x, y, blockMenu[layer][selected%80].first->getLayer(), blockMenu[layer][selected%80].first->getId(), blockMenu[layer][selected%80].second);
			}
		}
		else if(event.key.code == sf::Mouse::Right)
		{
			if (event.mouseButton.y < app.getSize().y-32)
			{
				int x = (int)(app.getView().getCenter().x-app.getView().getSize().x/2 + 256 + event.mouseButton.x)>>4;
				int y = (int)(app.getView().getCenter().y-app.getView().getSize().y/2 + 256 + event.mouseButton.y)>>4;

				world->setBlockAndMetadata(x, y, 2, 0, 0);
			}
		}
	}

}

void NoobishBlockMenu::Draw(App &app, TextureContainer &tC)
{
	for (int j = 0; j < 2; j++)
	{
		for(int i = 0; i < 80; ++i)
		{
			blockMenu[j][i].first->Draw(app.getView().getCenter().x - app.getSize().x/2 + (i<<4), (int)app.getView().getCenter().y + app.getSize().y/2 -32+16*j, app, tC, blockMenu[j][i].second);
		}
	}
}
#endif