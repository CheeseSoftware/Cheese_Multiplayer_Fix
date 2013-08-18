#include "BlockGravity.h"
#include "Entity.h"
#include "Creature.h"

BlockGravity::BlockGravity(unsigned short id) : Block(id)
{

}

unsigned short BlockGravity::getTextureId(App &app, unsigned short metadata)
{
	return metadata;
}

unsigned char BlockGravity::getLayer()
{
	return 2;
}

bool BlockGravity::isSolid()
{
	return false;
}

bool BlockGravity::isSeeThrough()
{
	return true;
}

std::string BlockGravity::getTextureName()
{
	return "BlockGravity.png";
}

void BlockGravity::OnEntityGravity(App &app, Entity *entity, float &xFriction, float&yFriction, float &speedX, float &speedY, unsigned short metadata)
{
	float strength = (1.0F+(metadata>>3)/2.0F)*app.getDeltaTime()*1000.0F;

	float friction = 1.0F-(1.0F-xFriction)*0.5F;//friction = 1;//(metadata&0x0004)? friction/strength : friction*strength;

	switch(metadata&0x0003)
	{
	case 1://up
		speedY -= strength;
		xFriction = friction;
		yFriction = yFriction*0.25;
		break;

	case 0://left
		speedX -= strength;
		yFriction = friction;
		xFriction = xFriction*0.25;
		break;

	case 2://right
		speedX += strength;
		yFriction = friction;
		xFriction = xFriction*0.25;
		break;

	case 3://down
		speedY += strength;
		xFriction = friction;
		yFriction = yFriction*0.25;
		break;
	}
}

void BlockGravity::getCreatureMovePossibilities(App &app, Creature *creature, float &horizontal, float &vertical, unsigned short metadata)
{
	switch(metadata&0x0003)
	{
	case 1://up
		vertical = 0;
		break;

	case 0://left
		horizontal = 0;
		break;

	case 2://right
		horizontal = 0;
		break;

	case 3://down
		vertical = 0;
		break;
	}
}

void BlockGravity::CreatureJump(App &app, Creature *creature, float &speedX, float &speedY, unsigned short metadata)
{
	switch(metadata&0x0003)
	{
	case 1://up
		speedY = 512;
		break;

	case 0://left
		speedX = 512;
		break;

	case 2://right
		speedX = -512;
		break;

	case 3://down
		speedY = -512;
		break;
	}
}