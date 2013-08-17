#pragma once
#include "Block.h"

class BlockGravity : public Block
{
public:
	BlockGravity(unsigned short id);
	virtual unsigned short getTextureId(App &app, unsigned short metadata);
	virtual unsigned char getLayer();
	virtual bool isSolid();
	virtual bool isSeeThrough();
	virtual std::string getTextureName();
	virtual void OnEntityGravity(App &app, Entity *entity, float &xFriction, float&yFriction, float &speedX, float &speedY, unsigned short metadata);
	virtual void getCreatureMovePossibilities(App &app, Creature *creature, float &horizontal, float &vertical, unsigned short metadata);
	//virtual void getGravityModifierAngle()=0;
	//virtual void getGravityStrength()=0;
	//virtual void getFrictionStrength()=0;
};

