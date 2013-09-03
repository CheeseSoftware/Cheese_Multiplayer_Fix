#include "Block.h"

class ISolid : Block
{
public:
	virtual bool isSolid();
	virtual unsigned char getLayer();
};