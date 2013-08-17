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

void BlockGravity::OnEntityGravity(App &app, Entity *entity, float &friction, float &speedX, float &speedY, unsigned short metadata)
{
	float strength = (1.0F+(metadata>>3)/2.0F)*app.getFrameTime()*4000.0F;

	//friction = 1;//(metadata&0x0004)? friction/strength : friction*strength;

	switch(metadata&0x0003)
	{
	case 0://up
		speedY -= strength;
		break;

	case 1://left
		speedX -= strength;
		break;

	case 2://right
		speedY += strength;
		break;

	case 3://down
		speedX += strength;
		break;
	}
}

void BlockGravity::getCreatureMovePossibilities(App &app, Creature *creature, bool &Up, bool &Left, bool &Right, bool &Down, unsigned short metadata)
{
	switch(metadata&0x0003)
	{
	case 0://up
		Up = false;
		Down = false;
		break;

	case 1://left
		Left = false;
		Right = false;
		break;

	case 2://right
		Left = false;
		Right = false;
		break;

	case 3://down
		Up = false;
		Down = false;
		break;
	}
}