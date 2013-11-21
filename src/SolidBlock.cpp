#include "SolidBlock.h"

bool SolidBlock::isSolid() const
{
	return true;
}

unsigned char SolidBlock::getLayer() const
{
	return 2;
}