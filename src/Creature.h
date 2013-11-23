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

	virtual inline void PhysicUpdate(App &app, World *world, float timeSpan);
public:
SERVER(
	Creature(float x, float y, short sizeX, short sizeY, float speed, float maxSpeed, float friction, std::string spriteName, int spriteIndex, bool isClientControlling);
)

	//virtual void Update(App &app, World *world, std::queue<sf::Packet> *packetDataList);
CLIENT(
	Creature(float x, float y, short sizeX, short sizeY, float speed, float maxSpeed, float friction, std::string spriteName, int spriteIndex, bool isClientControlling);
)
	//virtual void Update(App &app, World *world, std::queue<sf::Packet> *packetDataList,Camera *camera, EventHandler &EventHandler);

	virtual void Update(App &app, GameUtility *gameUtility);
	void CreatureMove(float x, float y, float speedX, float speedY, float angle, float horizontal, float vertical);
	virtual void OnProjectileHit(App &app, GameUtility *gameUtility, Projectile *projectile, float damage);
};