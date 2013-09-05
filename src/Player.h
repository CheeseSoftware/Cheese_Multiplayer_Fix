
#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <list>
#include "Creature.h"
#include "Inventory.h"
#include "Item.h"
#include "NormalItem.h"

class TextureContainer;
class Camera;
class Projectile;

class Player : public Creature
{
private:
    bool right;
    bool down;
    bool left;
    bool up;
	bool lmb;
	float cameraDelay;
    std::string name;
	Inventory* inventory;
public:
#ifdef _SERVER
	Player(float X, float Y, short sizeX, short sizeY,
		bool IsClientControlling, std::string spriteName, int spriteIndex, std::string Name);

	//virtual void Update(App &app, World *world, std::queue<sf::Packet> *packetDataList);
#else
	Player(float X, float Y, short sizeX, short sizeY,
		bool IsClientControlling, std::string spriteName, int spriteIndex, std::string Name);

	//virtual void Update(App &app, World *world, std::queue<sf::Packet> *packetDataList,Camera *camera, EventHandler &EventHandler);
#endif
	virtual void Update(App &app, GameUtility *GameUtility);

#ifndef _SERVER
	virtual void EventUpdate(App &app, const sf::Event &event, GameUtility* gameUtility);
    virtual void Draw(App &app, GameUtility *gameUtility);
#endif
    void KeyUpdate(bool Right, bool Down, bool Left, bool Up, GameUtility* gameUtility);
	void setCameraDelay(float delay);
	virtual std::string getTextureName();
	virtual char getTextureId();
};
