#include "BlockChest.h"

BlockChest::BlockChest(unsigned short id) 
	: Block(id)
{
	inventory = new Inventory(5, 5, 64);
	isDrawingInventory = false;
}


BlockChest::~BlockChest(void)
{
}

const char *const BlockChest::getTextureName() const
{
	return "BlockChest.png";
}

unsigned short BlockChest::getTextureId(App &app, unsigned short metadata) const
{
	return metadata;
}

bool BlockChest::isSeeThrough() const
{
	return false;
}

bool BlockChest::isUnique() const
{
	return true;
}

void BlockChest::OnRemove()
{
	//delete this;
}

bool BlockChest::OnRightClick(Creature *creature, const unsigned short metadata, const long x, const long y, const short layer, GameUtility *gameUtility)
{
	isDrawingInventory = !isDrawingInventory;//temp
	std::cout << "onrightclick" << std::endl;
	return true;
}

void BlockChest::OnEntityTouch(Entity *entity, const unsigned short metadata)
{
	std::cout << "entityovermeD:" << std::endl;
}

#ifndef _SERVER
void BlockChest::Draw(const long posX, const long posY, App &app, GameUtility *gameUtility, const unsigned short metadata)
{
	if(isDrawingInventory)
	{
		inventory->Draw(posX, posY - inventory->getSizeY()*32, app, gameUtility->getTextureContainer());
	}
	Block::Draw(posX, posY, app, gameUtility, metadata);
}
#endif
