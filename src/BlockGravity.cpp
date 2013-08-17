#include "BlockGravity.h"


BlockGravity::BlockGravity(unsigned short id) : Block(id)
{

}

void BlockGravity::OnEntityGravity(Entity *entity, float &friction, float &speedX, float &speedY, bool &Up, bool &Left, bool &Right, bool &Down, unsigned short metadata)
{
	float strength = 1.0F+(metadata>>3)/2.0F;

	friction = (metadata&0x0004)? friction/strength : friction*strength;

	switch(metadata&0x0003)
	{
	case 0://up
		speedY -= strength;
		Up = false;
		Down = false;
		break;

	case 1://left
		speedX -= strength;
		Left = false;
		Right = false;
		break;

	case 2://right
		speedY += strength;
		Left = false;
		Right = false;
		break;

	case 3://down
		speedX += strength;
		Up = false;
		Down = false;
		break;
	}
}