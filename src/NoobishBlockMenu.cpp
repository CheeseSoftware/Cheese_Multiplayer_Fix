#ifndef _SERVER
#include "NoobishBlockMenu.h"
#include "World.h"
#include "Block.h"
#include "TextureContainer.h"
#include <SFML\Network.hpp>
#include "BlockRegister.h"
#include "GameUtility.h"

/*//>.<NoobishBlockMenu::NoobishBlockMenu()
{

}*/

NoobishBlockMenu::NoobishBlockMenu(World *world, GameUtility* gameUtility)
{
	selected = 0;
	blockMenu = new std::pair<Block*, unsigned short>*[2];
	for(int i = 0; i < 2; i++)
	{
		blockMenu[i] = new std::pair<Block*, unsigned short>[80];
		for(int x = 0; x < 80; x++)
		{
			if (x < 50)
				blockMenu[i][x] = std::pair<Block*, unsigned short>(gameUtility->getBlockRegister().getBlockType(1+i), x);
			else
				blockMenu[i][x] = std::pair<Block*, unsigned short>(gameUtility->getBlockRegister().getBlockType(4), x%4);
		}
	}
}

void NoobishBlockMenu::EventUpdate(App &app, const sf::Event &event, GameUtility* gameUtility)
{
	if(event.type == sf::Event::MouseButtonPressed)
	{
		int x = (int)(app.getView().getCenter().x-app.getView().getSize().x/2 + 256 + event.mouseButton.x)>>4;
		int y = (int)(app.getView().getCenter().y-app.getView().getSize().y/2 + 256 + event.mouseButton.y)>>4;
		if(event.key.code == sf::Mouse::Left)
		{
			if (event.mouseButton.y >= app.getSize().y-32)
			{
				std::cout << "den gamla storkossan �r: " << selected << std::endl;
				//if (event.mouseButton.x <= 80*16)
				{
					int layer = (event.mouseButton.x >= app.getSize().y-16)? 1:0;
					selected = event.mouseButton.x>>4;
					std::cout << "den nya storkossan �r: " << selected << std::endl;
				}
			}
			else
			{
				int layer = (selected >= 80)? 1:0;
				gameUtility->getCurrentWorld()->setBlockAndMetadata(x, y,
					blockMenu[layer][selected%80].first->getLayer(),
					gameUtility->getBlockRegister().getBlockIdByTypeId(typeid(*blockMenu[layer][selected%80].first).hash_code()),
					blockMenu[layer][selected%80].second,
					gameUtility);
			}
		}
		else if(event.key.code == sf::Mouse::Right)
		{
			Block* block = gameUtility->getCurrentWorld()->getBlock(x, y, 2);
			if(block != nullptr)
				block->OnRightClick(nullptr, gameUtility->getCurrentWorld()->getBlockAndMetadata(x, y, 1).second);
			if (event.mouseButton.y < app.getSize().y-32)
			{
				gameUtility->getCurrentWorld()->setBlockAndMetadata(x, y, 2, 0, 0, gameUtility);
			}
		}
	}

}

void NoobishBlockMenu::Draw(App &app, GameUtility *gameUtility)
{
	for (int j = 0; j < 2; j++)
	{
		for(int i = 0; i < 80; ++i)
		{
			blockMenu[j][i].first->Draw(app.getView().getCenter().x - app.getSize().x/2 + (i<<4),
				(int)app.getView().getCenter().y + app.getSize().y/2 -32+16*j,
				app,
				gameUtility,
				blockMenu[j][i].second);
		}
	}
}
#endif