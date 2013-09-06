#pragma once
#include "Block.h"
#include "SolidBlock.h"

class BlockSolid : public virtual Block, public SolidBlock
{
public:
	BlockSolid(unsigned short id);
	virtual unsigned short getTextureId(App &app, unsigned short metadata);
	virtual std::string getTextureName();
};

