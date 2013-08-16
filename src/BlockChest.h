#pragma once
#include "Block.h"
class BlockChest : public Block
{
public:
	BlockChest(unsigned short id);
	~BlockChest(void);
	unsigned short getId();
	unsigned short getTextureId(App &app, unsigned short metadata);
	unsigned char getLayer();
	std::string getTextureName();
	bool isSeeThrough();
	bool isSolid();
};

