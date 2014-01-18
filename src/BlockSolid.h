#pragma once
#include "Block.h"
#include "SolidBlock.h"

class BlockSolid : public virtual Block, public SolidBlock
{
public:
	virtual unsigned short getTextureId(App &app, unsigned short metadata) const;
	virtual const char *const getTextureName() const;
};

