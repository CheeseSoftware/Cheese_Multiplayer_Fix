#include "BlockBackground.h"
#include "World.h"

BlockBackground::BlockBackground(unsigned short id) : Block(id)
{

}

std::string BlockBackground::getTextureName()
{
	return "BlockBackground.png";
}

unsigned short BlockBackground::getTextureId(App &app, unsigned short metadata)
{
	return metadata;
}