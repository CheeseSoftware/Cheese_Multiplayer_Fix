#include "BlockChest.h"


BlockChest::BlockChest(unsigned short id) 
	: Block(id)
{
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
	return(false);
}


void BlockChest::OnRightClick(Creature *creature, const unsigned short metadata)
{
	isDrawingInventory = !isDrawingInventory;//temp
	std::cout << "onrightclick" << std::endl;
}

void BlockChest::OnEntityTouch(Entity *entity, const unsigned short metadata)
{
	std::cout << "entityovermeD:" << std::endl;
}
