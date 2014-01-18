#pragma once
#include "Block.h"
#include "BackgroundBlock.h"

class BlockBackground : public virtual Block, public BackgroundBlock
{
public:
	virtual unsigned short getTextureId(App &app, const unsigned short metadata) const;
	virtual const char *const getTextureName() const;
};

