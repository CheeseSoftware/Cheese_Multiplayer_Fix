#include "Block.h"

class SolidBlock : virtual Block
{
public:
	virtual bool isSolid();
	virtual unsigned char getLayer();
};