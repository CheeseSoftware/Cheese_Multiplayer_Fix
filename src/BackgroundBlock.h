#include "Block.h"

class BackgroundBlock : virtual Block
{
public:
	virtual unsigned char getLayer();
	virtual bool isSolid();
};