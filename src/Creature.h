#pragma once

#include "Entity.h"
#include <SFML\Network.hpp>

class TextureContainer;
class Camera;

class Creature : public Entity
{
protected:
    float horizontal;
    float vertical;
public:
#ifdef _SERVER
	Creature(float x, float y, short sizeX, short sizeY, float speed, float friction, std::string spriteName, int spriteIndex, bool isClientControlling);

	//virtual void Update(App &app, World *world, std::queue<sf::Packet> *packetDataList);
#else
	Creature(float x, float y, short sizeX, short sizeY, float speed, float friction, std::string spriteName, int spriteIndex, bool isClientControlling);

	//virtual void Update(App &app, World *world, std::queue<sf::Packet> *packetDataList,Camera *camera, EventHandler &EventHandler);
#endif

	virtual void Update(App &app, SimulationState *simulationState, std::queue<sf::Packet> *packetDataList);
	void CreatureMove(float x, float y, float speedX, float speedY, float angle, float horizontal, float vertical);
};