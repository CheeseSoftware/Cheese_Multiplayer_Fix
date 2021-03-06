#pragma once
#define _USE_MATH_DEFINES

#include <SFML\Network.hpp>
#ifdef SERVER
#include <SFML\System.hpp>
#else
#include <SFML\Graphics.hpp>
#endif

#include <iostream>
#include "App.h"
#include "CollisionType.h"
#include "ISoundable.h"
enum MessageType;
class TextureContainer;
class World;
class Camera;
class GameUtility;
class Block;
class Game;

class Entity : public ISoundable
{
protected:
	int m_id;
    float x;
    float y;
    float speedX;
    float speedY;
	int sizeX;
	int sizeY;
    float friction;
    float angle;
    float speed;
	float maxSpeed;
	std::string spriteName;
	int spriteIndex;
	void FixateX();
	void FixateY();

	std::pair<Block*, unsigned short> currentBlock;

	virtual inline void PhysicUpdate(App &app, World *world, float timeSpan);
public:
    bool isClientControlling;

	Entity(int id, float x, float y, short sizeX, short sizeY,
		float angle, float speed, float maxSpeed, float friction, std::string spriteName,
		int spriteIndex, bool isClientControlling);
	virtual void Update(App &app, Game *game, GameUtility *gameUtility);
/*#ifdef SERVER
	virtual void Update(App &app, World *world, std::queue<sf::Packet> *packetDataList);
#else
	virtual void Update(App &app, World *world, std::queue<sf::Packet> *packetDataList,Camera *camera, EventHandler &EventHandler);
#endif*/
	
#ifdef CLIENT
	virtual void EventUpdate(App &app, Game *game, const sf::Event &event, GameUtility* gameUtility);
    virtual void Draw(App &app, Game *game, GameUtility *gameUtility);
#endif
	virtual CollisionType CheckCollision(App &app, Game *game, World *world, GameUtility *gameUtility, float speedX, float speedY);
	virtual void OnCollide(App &app, Game *game, World *world, GameUtility *gameUtility, float speedX, float speedY, CollisionType collisionType);
	virtual const char *const getTextureName()=0;
	virtual short getTextureId()=0;
    //void setPosition(float x, float y);
	virtual float getDistance(sf::Vector2f other) override;
	sf::Vector2f getPosition();
	void setSize(float x, float y);
	sf::Vector2f getSize();
    //void setX(float x);
    //void setY(float y);
    float getX();
    float getY();
	void setAngle(float angle);
	float getAngle();
	int getId() { return m_id; };
private:
	//virtual float getDeltaFriction(App &app, float xFriction, float yFriction);
};
