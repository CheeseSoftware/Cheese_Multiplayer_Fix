#pragma once
#include <SFML\Network.hpp>
#include "Entity.h"
class Projectile;
class TextureContainer;
class Camera;
class CreatureController;

class Creature : public Entity
{
protected:
    float horizontal;
    float vertical;
	float m_health;

	CreatureController *m_controller;

	virtual inline void PhysicUpdate(App &app, World *world, float timeSpan);
public:
	Creature(int id, float x, float y, short sizeX, short sizeY, float speed, float maxSpeed, float friction, std::string spriteName, int spriteIndex, bool isClientControlling);
	virtual void Update(App &app, Game *game, GameUtility *gameUtility);
	void setController(CreatureController *controller);
	void CreatureMove(float x, float y, float speedX, float speedY, float angle, float horizontal, float vertical);
	virtual void OnCollide(App &app, Game *game, World *world, GameUtility *gameUtility, float speedX, float speedY, CollisionType collisionType);
	virtual void OnProjectileHit(App &app, GameUtility *gameUtility, Projectile *projectile, float damage);
	virtual void OnDeath();
	virtual void OnDamage(float damage);
	virtual float getHealth() { return m_health; };
	virtual void setHealth(float health) { m_health = health; if(isDead()) OnDeath(); };
	virtual void Kill() { m_health = 0; OnDeath(); };
	virtual bool isDead() { return m_health <= 0; };
};