#pragma once
#include "SolidBlock.h"
#include "UniqueBlock.h"
class BlockChest : public SolidBlock
{
private:
	bool isDrawingInventory;
public:
	BlockChest(const unsigned short id);
	~BlockChest(void);
	//unsigned short getId();
	virtual unsigned short getTextureId(App &app, const unsigned short metadata) const;
	//unsigned char getLayer();
	virtual const char *const getTextureName() const;
	virtual bool isSeeThrough() const;
	//bool isSolid();
	virtual void OnRightClick(Creature *creature, const unsigned short metadata);
	virtual void BlockChest::OnEntityTouch(Entity *entity, const unsigned short metadata);
};

