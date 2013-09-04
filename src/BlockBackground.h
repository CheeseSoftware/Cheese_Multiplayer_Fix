#pragma once
#include "Block.h"
#include "IBackground.h"

class BlockBackground : public virtual Block, public virtual IBackground
{
public:
	BlockBackground(unsigned short id);
	virtual unsigned short getTextureId(App &app, unsigned short metadata);
	virtual std::string getTextureName();
};

