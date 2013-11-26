#ifndef _SERVER
#include "NoobishBlockMenu.h"
#include "World.h"
#include "Block.h"
#include "TextureContainer.h"
#include <SFML\Network.hpp>
#include "BlockRegister.h"
#include "GameUtility.h"

NoobishBlockMenu::NoobishBlockMenu(World *world, GameUtility* gameUtility)
	: selected(0)
	, layer(0)
{
	sf::Font *font = new sf::Font();
	if (!font->loadFromFile("font.ttf"))
		throw "font.ttf not found";
	sf::String *text = new sf::String("hello world");
	pos = new gui::Label(50, 50, text, font);
	menuItemContainer = new gui::MenuItemContainer(0, 0, 0, 0);
	menuItemContainer->Add(pos);

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
				layer = (event.mouseButton.y >= app.getSize().y-16)? 1:0;
				selected = event.mouseButton.x>>4;
				std::cout << "den nya storkossan är: " << selected << std::endl;
			}
			else
			{
				Block* block = gameUtility->getCurrentWorld()->getBlock(x, y, 2);
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || block == nullptr || !block->OnLeftClick(nullptr, gameUtility->getCurrentWorld()->getBlockAndMetadata(x, y, 2).second, x, y, 2, gameUtility))
				{
					long tempLayer = blockMenu[layer][selected%80].first->getLayer();
					unsigned short id = gameUtility->getBlockRegister().getBlockIdByTypeId(typeid(*blockMenu[layer][selected%80].first).hash_code());
					unsigned short metadata = blockMenu[layer][selected%80].second;
					gameUtility->getCurrentWorld()->SendSetBlockAndMetadata(x, y, tempLayer, id, metadata, gameUtility);
				}	
			}
		}
		else if(event.key.code == sf::Mouse::Right)
		{
			Block* block = gameUtility->getCurrentWorld()->getBlock(x, y, 2);
			if(block != nullptr)
			{
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				{
					block->OnRemove();
					gameUtility->getCurrentWorld()->SendSetBlockAndMetadata(x, y, 2, 0, 0, gameUtility);
				}
				else
				{
					if(!block->OnRightClick(nullptr, gameUtility->getCurrentWorld()->getBlockAndMetadata(x, y, 2).second, x, y, 2, gameUtility))
					{
						block->OnRemove();
						gameUtility->getCurrentWorld()->SendSetBlockAndMetadata(x, y, 2, 0, 0, gameUtility);
					}
				}
			}
		}
	}

}

void NoobishBlockMenu::Draw(App &app, GameUtility *gameUtility)
{
	std::string temp;
	std::ostringstream oss;
	oss << app.getFrameTime();
	pos->text->setString(sf::String(oss.str()));
	menuItemContainer->Draw(app);
	for (int j = 0; j < 2; j++)
	{
		for(int i = 0; i < 80; ++i)
		{
			blockMenu[j][i].first->Draw(i<<4, app.getSize().y -32+16*j, app, gameUtility, blockMenu[j][i].second);
		}
	}
}
#endif