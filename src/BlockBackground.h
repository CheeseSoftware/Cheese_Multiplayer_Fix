#pragma once
#include "Block.h"
#include "BackgroundBlock.h"

class BlockBackground : public virtual Block, public BackgroundBlock
{
public:
	BlockBackground(unsigned short id);
	virtual unsigned short getTextureId(App &app, unsigned short metadata);
	virtual std::string getTextureName();
};

