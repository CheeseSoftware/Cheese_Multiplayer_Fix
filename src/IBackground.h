#include "Block.h"

class IBackground : Block
{
	virtual unsigned char getLayer();
	virtual bool isSolid();
};