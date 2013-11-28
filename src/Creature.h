#pragma once

#include "Entity.h"
#include "Projectile.h"
#include <SFML\Network.hpp>

class TextureContainer;
class Camera;

class Creature : public Entity
{
protected:
    float horizontal;
    float vertical;
	int m_health;
	virtual inline void PhysicUpdate(App &app, World *world, float timeSpan);
public:
	Creature(float x, float y, short sizeX, short sizeY, float speed, float maxSpeed, float friction, std::string spriteName, int spriteIndex, bool isClientControlling);
	virtual void Update(App &app, GameUtility *gameUtility);
	void CreatureMove(float x, float y, float speedX, float speedY, float angle, float horizontal, float vertical);
	virtual void OnProjectileHit(App &app, GameUtility *gameUtility, Projectile *projectile, float damage);
	virtual void OnDeath(Creature *creature);
	virtual int getHealth() { return m_health; };
	virtual void setHealth(int health) { m_health = health; if(isDead()) OnDeath(this); };
	virtual void Damage(int damage) { m_health -= damage; if(isDead()) OnDeath(this); };
	virtual void Kill() { m_health = 0; OnDeath(this); };
	virtual bool isDead() { return m_health <= 0; };
};