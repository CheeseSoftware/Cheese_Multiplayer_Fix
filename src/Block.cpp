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

std::function<Block*(unsigned short)> Block::RegisterBlock(const unsigned short id)
{
	std::cout << typeid(*this).name() << '(' << typeid(*this).hash_code() << ") registered with blockId " << id << ".\n";
	if (isUnique())
	{
		return [&](unsigned short metadata) -> Block*
		{
			Block* block = static_cast<Block*>(malloc(sizeof(*this)));
			*block = *this;
			return block;
		};
	}
	else
	{
		return [&](unsigned short metadata) -> Block* { return this; };
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

Block *Block::OnReceive(sf::Packet* packet, GameUtility* gameUtility)
{
	sf::Int32 xPos;
	sf::Int32 yPos;
	sf::Uint16 layer;
	sf::Uint16 id;
	sf::Uint16 metadata;
	*packet >> xPos >> yPos >> layer >> id >> metadata;
#ifdef _SERVER
	gameUtility->getCurrentWorld()->setBlockAndMetadata(xPos, yPos, layer, id, metadata, gameUtility);
#else
	gameUtility->getCurrentWorld()->setBlockAndMetadataClientOnly(xPos, yPos, layer, id, metadata, gameUtility);
#endif
	return nullptr;
}

sf::Packet Block::OnSend(sf::Int16 packetType, long x, long y, short layer, short id, short metadata, GameUtility* gameUtility)
{
	sf::Packet packet = sf::Packet();
	switch (packetType)
	{
	case NullMessage:
		break;

	case BlockPlace:
		{
			std::cout << "client/server set " << x << " " << y << " " << layer << " " << id << " " << metadata << std::endl;
			packet << (sf::Int16)BlockPlace << (sf::Int32)x << (sf::Int32)y << (sf::Uint16)layer << (sf::Uint16)id << (sf::Uint16)metadata;
		}
		break;

	case BlockMetadataChange:
		{
			packet << (sf::Int16)BlockMetadataChange << (sf::Int32)x << (sf::Int32)y << (sf::Uint16)layer << (sf::Uint16)metadata;
		}
		break;

	default:
		{
			std::cout << "Unexpected Messagetype: " << packetType << "\n";
		}
		break;
	}
	return packet;
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