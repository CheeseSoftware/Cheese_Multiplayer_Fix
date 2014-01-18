#include "BlockSolid.h"

/*BlockSolid::BlockSolid(const unsigned short id) : Block(id)
{

}*/

const char *const BlockSolid::getTextureName() const
{
	return "BlockSolid.png";
}

unsigned short BlockSolid::getTextureId(App &app, const unsigned short metadata) const
{
	return metadata;
}