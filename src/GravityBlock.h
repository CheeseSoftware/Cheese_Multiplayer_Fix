#pragma once
#include "Block.h"

class GravityBlock : public virtual Block
{
public:
	virtual unsigned char getLayer() const;
	virtual bool isSolid() const;
	virtual bool isGravity() const;
};