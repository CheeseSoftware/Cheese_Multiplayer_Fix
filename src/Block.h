#pragma once
#include <iostream>
#include <functional>
#include "App.h" //#include <SFML/Graphics.hpp>
#include <SFML\Network.hpp>

class TextureContainer;
class World;
class Entity;
class Creature;
#include "EventHandler.h"//template<class T> class EventHandler;
class GameUtility;

class Block
{
public:
	Block();
	Block(const unsigned short id);

	virtual std::function<Block*(const unsigned short)> RegisterBlock(const unsigned short id);
	virtual unsigned short getTextureId(App &const app, const unsigned short metadata) const=0;
	virtual unsigned char getLayer() const=0;
	virtual const char *const getTextureName() const=0;
	virtual bool isSeeThrough() const;
	virtual bool isSolid() const=0;
	virtual bool isUnique() const;
	virtual bool isGravity() const;
#ifndef _SERVER
	virtual void OnCreate(const unsigned short metadata, EventHandler<GameUtility*> &eventHandler);
#else
	virtual void OnCreate(const unsigned short metadata);
#endif
	virtual void OnRemove();
	virtual void OnRightClick(Creature *creature, const unsigned short metadata, const long x, const long y, const short layer, GameUtility *gameUtility);
	virtual void OnEntityTouch(Entity *entity, const unsigned short metadata);
	virtual void OnEntitySlide(Entity *entity, float &friction, const unsigned short metadata);
	virtual void OnEntityHover(App &app, Entity *entity, float &xFriction, float&yFriction, float &speedX, float &speedY, const unsigned short metadata);
	virtual void getCreatureMovePossibilities(App &app, Creature *creature, float &horizontal, float &vertical, const unsigned short metadata);
	virtual void CreatureJump(App &app, Creature *creature, float &speedX, float &speedY, const unsigned short metadata);
	virtual void OnReceive(sf::Packet *packet, GameUtility *gameUtility);
	virtual void Block::OnSend(sf::Packet *packet, sf::Uint16 packetType, const long x, const long y, const short layer, const short id, const short metadata, GameUtility* gameUtility);
#ifndef _SERVER
	void Draw(const long posX, const long posY, App &app, GameUtility *gameUtility, const unsigned short metadata);
#endif
};