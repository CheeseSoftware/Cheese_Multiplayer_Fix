#include "BlockSolid.h"

BlockSolid::BlockSolid(unsigned short id) : Block(id)
{

}

std::string BlockSolid::getTextureName()
{
	return "BlockSolid.png";
}

unsigned short BlockSolid::getTextureId(App &app, unsigned short metadata)
{
	return metadata;
}