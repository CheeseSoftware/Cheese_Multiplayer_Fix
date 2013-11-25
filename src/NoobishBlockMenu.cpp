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
	: selected(0)
	, layer(0)
{
	blockMenu = new std::pair<Block*, unsigned short>*[2];
	for(int i = 0; i < 2; i++)
	{
		blockMenu[i] = new std::pair<Block*, unsigned short>[80];
		for(int x = 0; x < 80; x++)
		{
			if (x < 50)
				blockMenu[i][x] = std::pair<Block*, unsigned short>(gameUtility->getBlockRegister().getBlockType(1+i), x);
			else if (x < 54)
				blockMenu[i][x] = std::pair<Block*, unsigned short>(gameUtility->getBlockRegister().getBlockType(3), x%4);
			else if ( x < 55)
				blockMenu[i][x] = std::pair<Block*, unsigned short>(gameUtility->getBlockRegister().getBlockType(5), 0);
			else
				blockMenu[i][x] = std::pair<Block*, unsigned short>(gameUtility->getBlockRegister().getBlockType(4), x%4);
		}
	}
}

void NoobishBlockMenu::EventUpdate(App &app, const sf::Event &event, GameUtility* gameUtility)
{
	if(event.type == sf::Event::MouseButtonPressed)
	{
		int x = (int)(gameUtility->getCamera().getLeftX() + event.mouseButton.x)>>4;
		int y = (int)(gameUtility->getCamera().getTopY() + event.mouseButton.y)>>4;
		if(event.key.code == sf::Mouse::Left)
		{
			if (event.mouseButton.y >= app.getSize().y-32)
			{
				std::cout << "den gamla storkossan är: " << selected << std::endl;
				//if (event.mouseButton.x <= 80*16)
				{
					layer = (event.mouseButton.y >= app.getSize().y-16)? 1:0;
					selected = event.mouseButton.x>>4;
					std::cout << "den nya storkossan är: " << selected << std::endl;
				}
			}
			else
			{
				Block* block = gameUtility->getCurrentWorld()->getBlock(x, y, 2);
				if(block == nullptr || !block->OnLeftClick(nullptr, gameUtility->getCurrentWorld()->getBlockAndMetadata(x, y, 2).second, x, y, 2, gameUtility))
				{
					gameUtility->getCurrentWorld()->SendSetBlockAndMetadata(x, y,
						blockMenu[layer][selected%80].first->getLayer(),
						gameUtility->getBlockRegister().getBlockIdByTypeId(typeid(*blockMenu[layer][selected%80].first).hash_code()),
						blockMenu[layer][selected%80].second,
						gameUtility);
				}			
			}
		}
		else if(event.key.code == sf::Mouse::Right)
		{
			Block* block = gameUtility->getCurrentWorld()->getBlock(x, y, 2);
			//std::cout << "The block is unique:" << block->isUnique() << " texture:" << block->getTextureName() << std::endl;
			if(block != nullptr)
			{
				if(!block->OnRightClick(nullptr, gameUtility->getCurrentWorld()->getBlockAndMetadata(x, y, 2).second, x, y, 2, gameUtility))
				{
					block->OnRemove();
					gameUtility->getCurrentWorld()->SendSetBlockAndMetadata(x, y, 2, 0, 0, gameUtility);
				}
			}
			//if (event.mouseButton.y < app.getSize().y-32)
			//{
			//gameUtility->getCurrentWorld()->setBlockAndMetadata(x, y, 2, 0, 0, gameUtility);
			//}
		}
	}

}

void NoobishBlockMenu::Draw(App &app, GameUtility *gameUtility)
{
	for (int j = 0; j < 2; j++)
	{
		for(int i = 0; i < 80; ++i)
		{
			blockMenu[j][i].first->Draw(i<<4, app.getSize().y -32+16*j, app, gameUtility, blockMenu[j][i].second);
		}
	}
}
#endif