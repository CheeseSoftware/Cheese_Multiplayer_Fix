#pragma once
#include "Block.h"
#include "IBackground.h"

class BlockBackground : public Block, IBackground
{
public:
	BlockBackground(unsigned short id);
	virtual unsigned short getTextureId(App &app, unsigned short metadata);
	virtual std::string getTextureName();
};

