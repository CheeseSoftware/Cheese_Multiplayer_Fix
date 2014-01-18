#include "Stone.h"
#include "Block.h"

/*Stone::Stone(unsigned short metadata)
	: Block(metadata)
{
}

Stone::Stone()
	: Block()
{
}*/

unsigned short Stone::getTextureId(App &const app, const unsigned short metadata) const
{
	return metadata;
}

unsigned char Stone::getLayer() const
{
	return 2;
}

const char *const Stone::getTextureName() const
{
	return "stone.png";
}

unsigned const short Stone::getTextureSize() const
{
	return 64;
}
