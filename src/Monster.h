#pragma once

#include "Creature.h"

class Monster : public Creature
{
public:
	~Monster(void);

SERVER_(
	Monster(int id, float x, float y, short sizeX, short sizeY, float speed, float maxSpeed, float friction, std::string spriteName, int spriteIndex, bool isClientControlling);
)
	//virtual void Update(App &app, World *world, std::queue<sf::Packet> *packetDataList);
CLIENT_(
	Monster(int id, float x, float y, short sizeX, short sizeY, float speed, float maxSpeed, float friction, std::string spriteName, int spriteIndex, bool isClientControlling);
)
	//virtual void Update(App &app, World *world, std::queue<sf::Packet> *packetDataList,Camera *camera, EventHandler &EventHandler);

	virtual void Update(App &app, GameUtility *GameUtility);
};