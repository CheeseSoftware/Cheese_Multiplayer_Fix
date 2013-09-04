#include "Block.h"

class IGravity : virtual Block
{
public:
	virtual unsigned char getLayer();
	virtual bool isSolid();
};