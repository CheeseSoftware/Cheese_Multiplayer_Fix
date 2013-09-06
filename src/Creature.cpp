#include "Creature.h"
#include "Block.h"
#include "World.h"
#include "GameUtility.h"

#define PI 3.141592653589793238462643383279502884197169399375105820974944

Creature::Creature(float x, float y, short sizeX, short sizeY, float speed, float friction, std::string spriteName, int spriteIndex, bool isClientControlling) 
	: Entity(x,y,sizeX,sizeY,0,speed,friction,spriteName,spriteIndex,isClientControlling)
{
	horizontal = 0;
    vertical = 0;
}

/*#ifdef _SERVER
void Creature::Update(App &app, World *world, std::queue<sf::Packet> *packetDataList)
#else
void Creature::Update(App &app, World *world, std::queue<sf::Packet> *packetDataList, Camera *camera, EventHandler &eventHandler)
#endif*/
void Creature::Update(App &app, GameUtility *GameUtility)
{
	float horizontal2 = horizontal;
	float vertical2 = vertical;

	std::pair<Block*, unsigned short> blockAndMetadata = GameUtility->getCurrentWorld()->getBlockAndMetadata((long)x+8>>4,(long)y+8>>4, 2);//GameUtility->getCurrentWorld()->getBlockAndMetadata((long)x+8>>4,(long)y+8>>4, 2);
	if (blockAndMetadata.first != nullptr)
		blockAndMetadata.first->getCreatureMovePossibilities(app, this, horizontal2, vertical2, blockAndMetadata.second);

	speedX += horizontal2 * app.getDeltaTime();
    speedY += vertical2 * app.getDeltaTime();

	Entity::Update(app, GameUtility);
/*#ifdef _SERVER
	Entity::Update(app, world, packetDataList);
#else
	Entity::Update(app, world, packetDataList, camera, eventHandler);
#endif*/
}

void Creature::CreatureMove(float x, float y, float speedX, float speedY, float angle, float horizontal, float vertical)
{
	this->x = x;
	this->y = y;
	this->speedX = speedX;
	this->speedY = speedY;
	this->angle = angle;
	this->horizontal = horizontal;
	this->vertical = vertical;
}