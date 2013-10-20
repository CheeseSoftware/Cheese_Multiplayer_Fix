#pragma once
#include "Block.h"

class BackgroundBlock : public virtual Block
{
public:
	virtual unsigned char getLayer();
	virtual bool isSolid();
};