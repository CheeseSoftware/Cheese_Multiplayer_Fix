#pragma once
#include "Block.h"

class BackgroundBlock : public virtual Block
{
public:
	virtual unsigned char getLayer() const;
	virtual bool isSolid() const;
};