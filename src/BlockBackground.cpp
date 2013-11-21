#include "BlockBackground.h"
#include "World.h"

BlockBackground::BlockBackground(const unsigned short id) : Block(id)
{

}

const char *const BlockBackground::getTextureName() const
{
	return "BlockBackground.png";
}

unsigned short BlockBackground::getTextureId(App &app, const unsigned short metadata) const
{
	return metadata;
}