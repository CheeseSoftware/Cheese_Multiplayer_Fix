#include <SFML\Graphics.hpp>
#include "Creature.h"
#include "Monster.h"

Monster::Monster(int id, float x, float y, short sizeX, short sizeY, float speed, float maxSpeed, float friction, std::string spriteName, int spriteIndex, bool isClientControlling)
	: Creature(id, x, y, sizeX, sizeY, speed, maxSpeed, friction, spriteName, spriteIndex, isClientControlling)
{

}


Monster::~Monster(void)
{
}

/*#ifdef SERVER
void Monster::Update(App &app, World *world, std::queue<sf::Packet> *packetDataList)
#else
void Monster::Update(App &app, World *world, std::queue<sf::Packet> *packetDataList, Camera *camera, EventHandler &eventHandler)
#endif*/
void Monster::Update(App &app, GameUtility *GameUtility)
{
	Creature::Update(app, GameUtility);
/*#ifdef SERVER
	Creature::Update(app, world, packetDataList);
#else
	Creature::Update(app, world, packetDataList, camera, eventHandler);
#endif*/
}