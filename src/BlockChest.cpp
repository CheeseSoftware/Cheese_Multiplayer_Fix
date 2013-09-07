#include "BlockChest.h"


BlockChest::BlockChest(unsigned short id) 
	: Block(id)
{
	isDrawingInventory = false;
}


BlockChest::~BlockChest(void)
{
}

std::string BlockChest::getTextureName()
{
	return "BlockSolid.png";
}

unsigned short BlockChest::getTextureId(App &app, unsigned short metadata)
{
	return metadata;
}

bool BlockChest::isSeeThrough()
{
	return(false);
}


void BlockChest::OnRightClick(Creature *creature, unsigned short metadata)
{
	isDrawingInventory = !isDrawingInventory;//temp
	std::cout << "onrightclick" << std::endl;
}

void BlockChest::OnEntityTouch(Entity *entity, unsigned short metadata)
{
	std::cout << "entityovermeD:" << std::endl;
}
