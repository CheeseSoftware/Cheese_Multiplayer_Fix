#include <iostream>
#include <typeinfo>
#include "Block.h"
#include "TextureContainer.h"

Block::Block(unsigned short id)
{
	this->id = id;
}

std::function<Block*(unsigned short)> Block::RegisterBlock(const unsigned short id)
{
	std::cout << typeid(*this).name() << '(' << typeid(*this).hash_code() << ") registered with blockId " << id << ".\n";
	if (isUnique())
	{
		return [&](unsigned short metadata)
		{
			Block *block = (Block*)malloc(sizeof(*this));
			*block = *this;
			return block;
		};
	}
	else
	{
		return [&](unsigned short metadata) { return this; };
	}
}

unsigned short Block::getId()
{
	return id;
}

bool Block::isSeeThrough()
{
	return false;
}

bool Block::isSolid()
{
	return true;
}

bool Block::isUnique()
{
	return false;
}

void Block::OnCreate(unsigned short metadata, EventHandler &eventHandler)
{

}

void Block::OnRemove()
{
	if (isUnique())
	{
		delete this;
	}
}

void Block::OnRightClick(Creature *creature, unsigned short metadata)
{

}

void Block::OnEntityTouch(Entity *entity, unsigned short metadata)
{

}

void Block::OnEntitySlide(Entity *entity, float &friction, unsigned short metadata)
{

}

void Block::OnEntityHover(App &app, Entity *entity, float &xFriction, float&yFriction, float &speedX, float &speedY, unsigned short metadata)
{

}

void Block::getCreatureMovePossibilities(App &app, Creature *creature, float &horizontal, float &vertical, unsigned short metadata)
{

}

void Block::CreatureJump(App &app, Creature *creature, float &speedX, float &speedY, unsigned short metadata)
{

}

#ifndef _SERVER
void Block::Draw(long posX, long posY, App &app, TextureContainer &tC, unsigned short metadata)
{
	sf::Sprite *&&tempSprite = &(tC.getTextures(getTextureName())[getTextureId(app, metadata)]);
	if (tempSprite != nullptr)
	{
		tempSprite->setPosition(posX, posY);
		app.draw(*tempSprite);
	}
}
#endif