#include "Block.h"

class GravityBlock : virtual Block
{
public:
	virtual unsigned char getLayer();
	virtual bool isSolid();
};