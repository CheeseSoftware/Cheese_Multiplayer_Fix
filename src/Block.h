#pragma once
#include <iostream>
#include <functional>
#include "App.h" //#include <SFML/Graphics.hpp>

class TextureContainer;
class World;
class Entity;
class Creature;
class EventHandler;

class Block
{
private:
	unsigned short id;
public:
	Block(unsigned short id);

	unsigned short getId();

	virtual std::function<Block*(unsigned short)> RegisterBlock(const unsigned short id);
	virtual unsigned short getTextureId(App &app, unsigned short metadata)=0;
	virtual unsigned char getLayer()=0;
	virtual std::string getTextureName()=0;
	virtual bool isSeeThrough()=0;
	virtual bool isSolid()=0;
	virtual bool isUnique();
	virtual void OnCreate(unsigned short metadata, EventHandler &eventHandler);
	virtual void OnRemove();
	virtual void OnRightClick(Creature *creature, unsigned short metadata);
	virtual void OnEntityTouch(Entity *entity, unsigned short metadata);
	virtual void OnEntitySlide(Entity *entity, float &friction, unsigned short metadata);
	virtual void OnEntityGravity(Entity *entity, float &friction, float &speedX, float &speedY, bool &Up, bool &Left, bool &Right, bool &Down, unsigned short metadata);
	//virtual char getSubTextureId() = 0;
#ifndef _SERVER
	void Draw(long posX, long posY, App &app, TextureContainer &tC, unsigned short metadata);
#endif
};