#include "Block.h"

class ISolid : Block
{
	virtual bool isSolid();
	virtual unsigned char getLayer();
};