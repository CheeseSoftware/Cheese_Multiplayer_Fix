#pragma once
#include "Block.h"
class BlockChest : public Block
{
private:
	bool isDrawingInventory;
public:
	BlockChest(unsigned short id);
	~BlockChest(void);
	unsigned short getId();
	unsigned short getTextureId(App &app, unsigned short metadata);
	unsigned char getLayer();
	std::string getTextureName();
	bool isSeeThrough();
	bool isSolid();
	void OnRightClick(Creature *creature, unsigned short metadata);
	void BlockChest::OnEntityTouch(Entity *entity, unsigned short metadata);
};

