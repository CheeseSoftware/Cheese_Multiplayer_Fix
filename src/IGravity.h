#include "Block.h"

class IGravity
{
public:
	virtual unsigned char getLayer();
	virtual bool isSolid();
};