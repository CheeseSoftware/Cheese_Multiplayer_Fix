#include "BlockGravity.h"
#include "Entity.h"
#include "Creature.h"

/*BlockGravity::BlockGravity(const unsigned short id) : Block(id)
{

}*/

unsigned short BlockGravity::getTextureId(App &app, const unsigned short metadata) const
{
	return metadata;
}

bool BlockGravity::isSeeThrough() const
{
	return true;
}

const char *const BlockGravity::getTextureName() const
{
	return "BlockGravity.png";
}

void BlockGravity::OnEntityHover(App &app, Entity *entity, float &xFriction, float&yFriction, float &speedX, float &speedY, const unsigned short metadata)
{
	float strength = (1.0F+(metadata>>3)/2.0F)*app.getDeltaTime()*1200.f;//1550.0F;

	float friction = 1.0F-(1.0F-xFriction)*0.75F;//friction = 1;//(metadata&0x0004)? friction/strength : friction*strength;

	switch(metadata&0x0003)
	{
	case 1://up
		speedY -= strength;
		xFriction = friction;
		yFriction = yFriction*0.25F;
		break;

	case 0://left
		speedX -= strength;
		yFriction = friction;
		xFriction = xFriction*0.25F;
		break;

	case 2://right
		speedX += strength;
		yFriction = friction;
		xFriction = xFriction*0.25F;
		break;

	case 3://down
		speedY += strength;
		xFriction = friction;
		yFriction = yFriction*0.25F;
		break;
	}
}

void BlockGravity::getCreatureMovePossibilities(App &app, Creature *creature, float &horizontal, float &vertical, const unsigned short metadata)
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

void BlockGravity::CreatureJump(App &app, Creature *creature, float &speedX, float &speedY, const unsigned short metadata)
{
	switch(metadata&0x0003)
	{
	case 1://up
		speedY = 300;
		break;

	case 0://left
		speedX = 300;
		break;

	case 2://right
		speedX = -300;
		break;

	case 3://down
		speedY = -300;
		break;
	}
}