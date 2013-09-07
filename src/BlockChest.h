#pragma once
#include "SolidBlock.h"
#include "UniqueBlock.h"
class BlockChest : public SolidBlock
{
private:
	bool isDrawingInventory;
public:
	BlockChest(unsigned short id);
	~BlockChest(void);
	//unsigned short getId();
	unsigned short getTextureId(App &app, unsigned short metadata);
	//unsigned char getLayer();
	std::string getTextureName();
	bool isSeeThrough();
	//bool isSolid();
	void OnRightClick(Creature *creature, unsigned short metadata);
	void BlockChest::OnEntityTouch(Entity *entity, unsigned short metadata);
};

