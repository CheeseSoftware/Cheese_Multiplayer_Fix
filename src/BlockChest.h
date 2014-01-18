#pragma once
#include "SolidBlock.h"
#include "UniqueBlock.h"
#include "Inventory.h"
#include "Block.h"
#include "GameUtility.h"

class BlockChest : public SolidBlock
{
private:
	Inventory *inventory;
	bool isDrawingInventory;
public:
	BlockChest();
	~BlockChest(void);
	//unsigned short getId();
	virtual unsigned short getTextureId(App &app, const unsigned short metadata) const;
	//unsigned char getLayer();
	virtual const char *const getTextureName() const;
	virtual bool isSeeThrough() const;
	virtual bool isUnique() const;
	virtual void OnRemove();
	//bool isSolid();
	virtual bool OnRightClick(Creature *creature, const unsigned short metadata, const long x, const long y, const short layer, GameUtility *gameUtility);
	virtual void BlockChest::OnEntityTouch(Entity *entity, const unsigned short metadata);
#ifndef _SERVER
	virtual void Draw(const long posX, const long posY, App &app, GameUtility *gameUtility, const unsigned short metadata);
#endif
};

