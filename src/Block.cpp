#include <iostream>
#include <typeinfo>
#include "Block.h"
#include "TextureContainer.h"
#include "GameUtility.h"
#include "BlockRegister.h"

Block::Block()
{

}

Block::Block(unsigned short id)
{
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

bool Block::isSeeThrough()
{
	return false;
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

Block *Block::OnReceive(GameUtility*, sf::Packet*)
{
	return nullptr;
}

sf::Packet *Block::OnSend(GameUtility*)
{
	return nullptr;
}

#ifndef _SERVER
void Block::Draw(long posX, long posY, App &app, GameUtility *gameUtility, unsigned short metadata)
{
	sf::Sprite *tempSprite = &gameUtility->getBlockRegister().getBlockTextures(this)[getTextureId(app, metadata)]; //&(tC.getTextures(getTextureName())[getTextureId(app, metadata)]);
	if (tempSprite != nullptr)
	{
		tempSprite->setPosition(posX, posY);
		app.draw(*tempSprite);
	}
}
#endif