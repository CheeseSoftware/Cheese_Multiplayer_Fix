#include "Creature.h"
#include "Block.h"
#include "World.h"
#include "GameUtility.h"

#define PI 3.141592653589793238462643383279502884197169399375105820974944

Creature::Creature(float x, float y, short sizeX, short sizeY, float speed, float maxSpeed, float friction, std::string spriteName, int spriteIndex, bool isClientControlling) 
	: Entity(x,y,sizeX,sizeY,0,speed, maxSpeed, friction,spriteName,spriteIndex,isClientControlling)
{
	horizontal = 0;
    vertical = 0;
}

void Creature::PhysicUpdate(App &app, World *world, float timeSpan)
{
	float horizontal2 = horizontal;
	float vertical2 = vertical;

	if (currentBlock.first != nullptr)
		currentBlock.first->getCreatureMovePossibilities(app, this, horizontal2, vertical2, currentBlock.second);

	float xFriction = friction;
	float yFriction = friction;
	speedX += horizontal2 * app.getDeltaTime() * (pow(1-xFriction, app.getDeltaTime()));
    speedY += vertical2 * app.getDeltaTime() * (pow(1-yFriction, app.getDeltaTime()));
	Entity::PhysicUpdate(app, world, timeSpan);
}

void Creature::Update(App &app, GameUtility *GameUtility)
{
	Entity::Update(app, GameUtility);
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

void Creature::OnProjectileHit(App &app, GameUtility *gameUtility, Projectile *projectile, float damage)
{
	Damage(damage);
}

void Creature::OnDeath(Creature *creature)
{

}