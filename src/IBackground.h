#include "Block.h"

class IBackground : Block
{
public:
	virtual unsigned char getLayer();
	virtual bool isSolid();
};