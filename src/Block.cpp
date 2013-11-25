#include <iostream>
#include <typeinfo>
#include "Block.h"
#include "TextureContainer.h"
#include "GameUtility.h"
#include "BlockRegister.h"
#include "MessageType.h"

Block::Block()
{

}

Block::Block(unsigned short id)
{
}

std::function<Block*(const unsigned short)> Block::RegisterBlock(const unsigned short id)
{
	std::cout << typeid(*this).name() << '(' << typeid(*this).hash_code() << ") registered with blockId " << id << ".\n";
	/*if (isUnique())
	{
		return [&](unsigned short metadata) -> Block*
		{
			Block* block = static_cast<Block*>(malloc(sizeof(*this)));
			*block = *this;
			return block;
		};
	}
	else*/
	{
		return [&](unsigned short metadata) -> Block* { return this; };
	}
}

bool Block::isSeeThrough() const
{
	return false;
}

bool Block::isUnique() const
{
	return false;
}

bool Block::isGravity() const
{
	return false;
}

#ifndef _SERVER
void Block::OnCreate(const unsigned short metadata, EventHandler<GameUtility*> &eventHandler)
#else
void Block::OnCreate(const unsigned short metadata)
#endif
{

}

void Block::OnRemove()
{
	if (isUnique())
	{
		delete this;
	}
}

void Block::OnRightClick(Creature *creature, const unsigned short metadata, const long x, const long y, const short layer, GameUtility *gameUtility)
{
	OnRemove();
	gameUtility->getCurrentWorld()->setBlockAndMetadata(x, y, layer, 0, 0, gameUtility);
}

void Block::OnEntityTouch(Entity *entity, const unsigned short metadata)
{

}

void Block::OnEntitySlide(Entity *entity, float &friction, const unsigned short metadata)
{

}

void Block::OnEntityHover(App &app, Entity *entity, float &xFriction, float&yFriction, float &speedX, float &speedY, const unsigned short metadata)
{

}

void Block::getCreatureMovePossibilities(App &app, Creature *creature, float &horizontal, float &vertical, const unsigned short metadata)
{

}

void Block::CreatureJump(App &app, Creature *creature, float &speedX, float &speedY, const unsigned short metadata)
{

}

void Block::OnReceive(sf::Packet* packet, sf::Uint16 id, GameUtility* gameUtility)
{
	sf::Int32 xPos;
	sf::Int32 yPos;
	sf::Uint16 layer;
	sf::Uint16 metadata;
	*packet >> xPos >> yPos >> layer >> metadata;
	if(layer < 0 || layer > 6)
	{
		std::cout << "wtf layer" << std::endl;
		return;
	}
	//std::cout << "received block: id:" << id << " layer:" << layer << std::endl;
#ifdef _SERVER
	gameUtility->getCurrentWorld()->setBlockAndMetadata(xPos, yPos, layer, id, metadata, gameUtility);
#else
	gameUtility->getCurrentWorld()->setBlockAndMetadataLocal(xPos, yPos, layer, id, metadata, gameUtility);
#endif
}

void Block::OnSend(sf::Packet *packet, sf::Uint16 packetType, long x, long y, short layer, short id, short metadata, GameUtility* gameUtility)
{
	switch (packetType)
	{
	case BlockPlace:
		*packet << (sf::Uint16)id << (sf::Int32)x << (sf::Int32)y << (sf::Uint16)layer << (sf::Uint16)metadata;
		break;
	case BlockMetadataChange:
		*packet << (sf::Int32)x << (sf::Int32)y << (sf::Uint16)layer << (sf::Uint16)metadata;
		break;
	default:
		std::cout << "Unexpected Messagetype: " << packetType << "\n";
		break;
	}
}

#ifndef _SERVER
void Block::Draw(const long posX, const long posY, App &app, GameUtility *gameUtility, const unsigned short metadata)
{
	sf::Sprite *tempSprite = &gameUtility->getBlockRegister().getBlockTextures(this)[getTextureId(app, metadata)]; //&(tC.getTextures(getTextureName())[getTextureId(app, metadata)]);
	if (tempSprite != nullptr)
	{
		tempSprite->setPosition(posX, posY);
		app.draw(*tempSprite);
	}
}
#endif