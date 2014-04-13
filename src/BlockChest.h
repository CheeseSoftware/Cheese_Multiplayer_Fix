#pragma once
#include "SolidBlock.h"
class Inventory;
class GameUtility;

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
#ifdef CLIENT
	virtual void Draw(const long posX, const long posY, App &app, Game *game, GameUtility *gameUtility, const unsigned short metadata);
#endif
};

