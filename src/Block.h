#pragma once
#include <iostream>
#include <functional>
#include "App.h" //#include <SFML/Graphics.hpp>
#include <SFML\Network.hpp>

class TextureContainer;
class World;
class Entity;
class Creature;
class EventHandler;
class GameUtility;

class Block
{
public:
	Block();
	Block(unsigned short id);

	virtual std::function<Block*(unsigned short)> RegisterBlock(const unsigned short id);
	virtual unsigned short getTextureId(App &app, unsigned short metadata)=0;
	virtual unsigned char getLayer()=0;
	virtual std::string getTextureName()=0;
	virtual bool isSeeThrough();
	virtual bool isSolid()=0;
	virtual bool isUnique();
	virtual void OnCreate(unsigned short metadata, EventHandler &eventHandler);
	virtual void OnRemove();
	virtual void OnRightClick(Creature *creature, unsigned short metadata);
	virtual void OnEntityTouch(Entity *entity, unsigned short metadata);
	virtual void OnEntitySlide(Entity *entity, float &friction, unsigned short metadata);
	virtual void OnEntityHover(App &app, Entity *entity, float &xFriction, float&yFriction, float &speedX, float &speedY, unsigned short metadata);
	virtual void getCreatureMovePossibilities(App &app, Creature *creature, float &horizontal, float &vertical, unsigned short metadata);
	virtual void CreatureJump(App &app, Creature *creature, float &speedX, float &speedY, unsigned short metadata);
	virtual Block *OnReceive(GameUtility*, sf::Packet*);
	virtual sf::Packet *OnSend(GameUtility*);
	//virtual char getSubTextureId() = 0;
#ifndef _SERVER
	void Draw(long posX, long posY, App &app, GameUtility *gameUtility, unsigned short metadata);
#endif
};