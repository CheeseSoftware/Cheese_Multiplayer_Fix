#pragma once
#include <iostream>
#include <functional>
#include "App.h" //#include <SFML/Graphics.hpp>

class TextureContainer;
class World;
class Entity;

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
	virtual bool isSimple();
	//virtual float getFrictionStrength();
	//virtual void EntityTouch(Entity *entity);
	//virtual void EntitySlide(Entity *entity, float &friction);
	//virtual void EntityGravity(Entity *entity, float &friction, float &speed, bool);
	//virtual char getSubTextureId() = 0;
#ifndef _SERVER
	void Draw(long posX, long posY, App &app, TextureContainer &tC, unsigned short metadata);
#endif
};