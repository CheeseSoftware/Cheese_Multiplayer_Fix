#include "Block.h"

class ISolid : virtual Block
{
public:
	virtual bool isSolid();
	virtual unsigned char getLayer();
};