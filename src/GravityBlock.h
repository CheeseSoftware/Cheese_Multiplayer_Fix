#pragma once
#include "Block.h"

class GravityBlock : public virtual Block
{
public:
	virtual unsigned char getLayer();
	virtual bool isSolid();
};