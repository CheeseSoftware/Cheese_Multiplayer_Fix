#pragma once
#include "Block.h"
#include "GravityBlock.h"

class BlockGravity : public virtual Block, public GravityBlock
{
public:
	BlockGravity(const unsigned short id);
	virtual unsigned short getTextureId(App &app, const unsigned short metadata) const;
	virtual bool isSeeThrough() const;
	virtual const char *const getTextureName() const;
	virtual void OnEntityHover(App &app, Entity *entity, float &xFriction, float&yFriction, float &speedX, float &speedY, const unsigned short metadata);
	virtual void getCreatureMovePossibilities(App &app, Creature *creature, float &horizontal, float &vertical, const unsigned short metadata);
	virtual void CreatureJump(App &app, Creature *creature, float &speedX, float &speedY, const unsigned short metadata);
	//virtual void getGravityModifierAngle()=0;
	//virtual void getGravityStrength()=0;
	//virtual void getFrictionStrength()=0;
};

