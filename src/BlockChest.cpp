#include "BlockChest.h"


BlockChest::BlockChest(unsigned short id) 
	: Block(id)
{

}


BlockChest::~BlockChest(void)
{
}

std::string BlockChest::getTextureName()
{
	return "BlockChest.png";
}

unsigned short BlockChest::getTextureId(App &app, unsigned short metadata)
{
	return metadata;
}

unsigned short BlockChest::getId()
{
	return 3;
}

bool BlockChest::isSeeThrough()
{
	return(false);
}

bool BlockChest::isSolid()
{
	return(true);
}

unsigned char BlockChest::getLayer()
{
	return 2;
}
