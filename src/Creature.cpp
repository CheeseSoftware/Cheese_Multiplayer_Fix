#include "Creature.h"
#include "Block.h"
#include "World.h"
#include "GameUtility.h"
#include "MessageType.h"

#define PI 3.141592653589793238462643383279502884197169399375105820974944

Creature::Creature(int id, float x, float y, short sizeX, short sizeY, float speed, float maxSpeed, float friction, std::string spriteName, int spriteIndex, bool isClientControlling) 
	: Entity(id, x,y,sizeX,sizeY,0,speed, maxSpeed, friction,spriteName,spriteIndex,isClientControlling)
{
	horizontal = 0;
	vertical = 0;
	m_health = 100;
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

void Creature::Update(App &app, GameUtility *gameUtility)
{
	Entity::Update(app, gameUtility);
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

void Creature::OnCollide(App &app, World *world, GameUtility *gameUtility, float speedX, float speedY, CollisionType collisionType)
{
	if(collisionType == CollisionType::YAxis && speedY > 2)
	{
#ifdef _SERVER
		std::cout << "Damaged " << speedY*30 << " ! Health left: " << getHealth() << std::endl;
		Damage(speedY*30);
		sf::Packet packet;
		packet << (sf::Uint16)MessageType::CreatureDamage << (sf::Uint16)getId() << (sf::Uint32)speedY*30;
		gameUtility->SendPacket(packet);
#endif
	}
}

void Creature::OnProjectileHit(App &app, GameUtility *gameUtility, Projectile *projectile, float damage)
{
	Damage(damage);
}

void Creature::OnDeath()
{

}

void Creature::OnDamage(int damage)
{

}