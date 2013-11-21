#pragma once
#include "Block.h"

class SolidBlock : public virtual Block
{
public:
	virtual bool isSolid() const;
	virtual unsigned char getLayer() const;
};