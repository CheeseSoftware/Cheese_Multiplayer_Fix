#pragma once
#include "Block.h"

class SolidBlock : public virtual Block
{
public:
	virtual bool isSolid();
	virtual unsigned char getLayer();
};