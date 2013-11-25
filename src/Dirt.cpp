#include "Dirt.h"
#include "Block.h"

Dirt::Dirt(unsigned short metadata)
	: Block(metadata)
{
}

Dirt::Dirt()
	: Block()
{
}

unsigned short Dirt::getTextureId(App &const app, const unsigned short metadata) const
{
	return metadata;
}

unsigned char Dirt::getLayer() const
{
	return 2;
}

const char *const Dirt::getTextureName() const
{
	return "dirt.png";
}

unsigned const short Dirt::getTextureSize() const
{
	return 32;
}
