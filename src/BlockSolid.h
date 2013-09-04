#pragma once
#include "Block.h"
#include "ISolid.h"

class BlockSolid : public virtual Block, public virtual ISolid
{
public:
	BlockSolid(unsigned short id);
	virtual unsigned short getTextureId(App &app, unsigned short metadata);
	virtual std::string getTextureName();
};

