#include "Block.h"

class IBackground : virtual Block
{
public:
	virtual unsigned char getLayer();
	virtual bool isSolid();
};