#include "GravityBlock.h"

unsigned char GravityBlock::getLayer() const
{
	return 2;
}

bool GravityBlock::isSolid() const
{
	return false;
}