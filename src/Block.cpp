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

bool Block::isUnique()
{
	return false;
}

void Block::onRemove()
{
	if (isUnique())
	{
		delete this;
	}
}

void Block::onRightClick(Creature *creature)
{

}

void Block::EntityTouch(Entity *entity)
{

}

void Block::EntitySlide(Entity *entity, float &friction)
{

}

void Block::EntityGravity(Entity *entity, float &friction, float &speed, bool)
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