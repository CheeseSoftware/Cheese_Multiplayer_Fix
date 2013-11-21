//class Entity;
#pragma once

#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#include "App.h"
#ifdef _SERVER
#include <SFML\System.hpp>
#else
#include <SFML\Graphics.hpp>
#endif
#include <SFML\Network.hpp>

enum MessageType;
class TextureContainer;
class World;
class Camera;
//template<class T> class EventHandler;
class GameUtility;

class Entity
{
protected:
    float x;
    float y;
    float speedX;
    float speedY;
	int sizeX;
	int sizeY;
    float friction;
    float angle;
    float speed;
	std::string spriteName;
	int spriteIndex;
	void FixateX();
	void FixateY();

	virtual inline void PhysicUpdate(App &app, World *world, float timeSpan);
public:
    bool isClientControlling;

	Entity(float x, float y, short sizeX, short sizeY,
		float angle, float speed, float friction, std::string spriteName,
		int spriteIndex, bool isClientControlling);
	virtual void Update(App &app, GameUtility *GameUtility);
/*#ifdef _SERVER
	virtual void Update(App &app, World *world, std::queue<sf::Packet> *packetDataList);
#else
	virtual void Update(App &app, World *world, std::queue<sf::Packet> *packetDataList,Camera *camera, EventHandler &EventHandler);
#endif*/
	
#ifndef _SERVER
	virtual void EventUpdate(App &app, const sf::Event &event, GameUtility* gameUtility);
    virtual void Draw(App &app, GameUtility *gameUtility);
#endif
	virtual bool CheckCollision(App &app, World *world, float speedX, float speedY);
	virtual void Collision(World *world);
	virtual const char *const getTextureName()=0;
	virtual short getTextureId()=0;
    void setPosition(float x, float y);
	sf::Vector2f getPosition();
	void setSize(float x, float y);
	sf::Vector2f getSize();
    void setX(float x);
    void setY(float y);
    float getX();
    float getY();
	void setAngle(float angle);
	float getAngle();
private:
	//virtual float getDeltaFriction(App &app, float xFriction, float yFriction);
};
