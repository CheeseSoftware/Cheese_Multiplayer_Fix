#include <math.h>

#include "Block.h"
#include "Entity.h"
#include "EventHandler.h"
#include "TextureContainer.h"
#include "World.h"
#include "GameUtility.h"

Entity::Entity(int id, float x, float y, short sizeX, short sizeY,
			   float angle, float speed, float maxSpeed, float friction, std::string spriteName,
			   int spriteIndex, bool isClientControlling)
			   : m_id(id)
			   , x(x)
			   , y(y)
			   , speed(speed)
			   , maxSpeed(maxSpeed)
			   , friction(friction)
			   , isClientControlling(isClientControlling)
			   , sizeX(sizeX)
			   , sizeY(sizeY)
			   , angle(angle)
			   , spriteName(spriteName)
			   , spriteIndex(spriteIndex)
			   , speedX(0)
			   , speedY(0)
{

}

void Entity::PhysicUpdate(App &app, World *world, float timeSpan)
{
	float xFriction = friction;
	float yFriction = friction;

	if (currentBlock.first != nullptr)
		currentBlock.first->OnEntityHover(app, this, xFriction, yFriction, speedX, speedY, currentBlock.second);

	speedX *= pow(1.0-xFriction,app.getDeltaTime());//pow(1-xFriction, app.getDeltaTime());//tan(xFriction*M_PI/2) * app.getDeltaTime();
	speedY *= pow(1.0-yFriction,app.getDeltaTime());//pow(1-yFriction, app.getDeltaTime());//tan(yFriction*M_PI/2) * app.getDeltaTime();

	if		(speedX > maxSpeed)		speedX = maxSpeed;
	else if	(speedX < -maxSpeed)	speedX = -maxSpeed;
	if		(speedY > maxSpeed)		speedY = maxSpeed;
	else if	(speedY < -maxSpeed)	speedY = -maxSpeed;
}

void Entity::Update(App &app, GameUtility *gameUtility)
{
	currentBlock = gameUtility->getCurrentWorld()->getBlockAndMetadata(
		(long)x>>4L,
		(long)y>>4L,
		2);

	if (currentBlock.first != nullptr)
	{
		if (!currentBlock.first->isGravity())
			currentBlock = gameUtility->getCurrentWorld()->getPhysicBlock();
	}
	else
	{
		currentBlock = gameUtility->getCurrentWorld()->getPhysicBlock();
	}

	PhysicUpdate(app, gameUtility->getCurrentWorld(), app.getDeltaTime());

	if (speedX != 0.0F || speedY != 0.0F)
	{
		float speedXModifier = abs(speedX * app.getDeltaTime());
		float speedYModifier = abs(speedY * app.getDeltaTime());

		char speedXNegativeFactor = (speedX > 0)? 1:-1;
		char speedYNegativeFactor = (speedY > 0)? 1:-1;

		double speed = sqrt(pow(speedX*app.getDeltaTime(),2)+pow(speedY*app.getDeltaTime(),2));
		double angle = atan2(speedY, speedX);

		double deltaX = cos(angle);
		double deltaY = sin(angle);

		for (int i = 0; i < 2; i++)
		{
			while(speed >= 1)
			{
				if (CheckCollision(app, gameUtility->getCurrentWorld(), gameUtility, deltaX, deltaY))
					break;

				x += deltaX;
				y += deltaY;

				speed -= 1;
			}
			if (speedX == 0)
				deltaX = 0;

			if (speedY == 0)
				deltaY = 0;
		}

		while (speedXModifier >= 1 && speedYModifier >= 1)
		{
			if (CheckCollision(app, gameUtility->getCurrentWorld(), gameUtility, (float)speedXNegativeFactor, (float)speedYNegativeFactor))
				break;

			if (speedX != 0 && speedY != 0)
			{
				x += speedXNegativeFactor;
				y += speedYNegativeFactor;

				speedXModifier -= 1;
				speedYModifier -= 1;
			}
			else
			{
				break;
			}
		}

		while(speedXModifier >= 1)
		{
			if (CheckCollision(app, gameUtility->getCurrentWorld(), gameUtility, (float)speedXNegativeFactor, 0))
				break;

			if (speedX != 0)
			{
				x += speedXNegativeFactor;

				speedXModifier -= 1;
			}
			else
			{
				break;
			}
		}

		while(speedYModifier >= 1)
		{
			if (CheckCollision(app, gameUtility->getCurrentWorld(), gameUtility, 0, (float)speedYNegativeFactor))
				break;

			if (speedY != 0)
			{
				y += speedYNegativeFactor;

				speedYModifier -= 1;
			}
			else
			{
				break;
			}
		}

		CheckCollision(app, gameUtility->getCurrentWorld(), gameUtility, speedXModifier*speedXNegativeFactor, speedYModifier*speedYNegativeFactor);

		if (speedX != 0)
			x += speedXModifier*speedXNegativeFactor;

		if (speedY != 0)
			y += speedYModifier*speedYNegativeFactor;

		CheckCollision(app, gameUtility->getCurrentWorld(), gameUtility, speedX * app.getDeltaTime(), speedY * app.getDeltaTime());
	}
}

CollisionType Entity::CheckCollision(App &app, World *world, GameUtility *gameUtility, float speedX, float speedY)
{
	CollisionType r = None;

	if (speedX == 0 && speedY == 0)
		return None;

	if (world->isBlockSolid((int)(x-(sizeX>>1)+speedX+0.5F)>>4,(int)(y-(sizeY>>1)+0.5F)>>4) ||
		world->isBlockSolid((int)(x+(sizeX>>1)+speedX-0.5F)>>4,(int)(y-(sizeY>>1)+0.5F)>>4) ||
		world->isBlockSolid((int)(x-(sizeX>>1)+speedX+0.5F)>>4,(int)(y+(sizeY>>1)-0.5F)>>4) ||
		world->isBlockSolid((int)(x+(sizeX>>1)+speedX-0.5F)>>4,(int)(y+(sizeY>>1)-0.5F)>>4))
	{
		OnCollide(app, world, gameUtility, speedX, speedY, XAxis);
		this->speedX = 0;
		speedX = 0;
		r = XAxis;
	}

	if (world->isBlockSolid((int)(x-(sizeX>>1)+0.5F)>>4,(int)(y-(sizeY>>1)+speedY+0.5F)>>4) ||
		world->isBlockSolid((int)(x+(sizeX>>1)-0.5F)>>4,(int)(y-(sizeY>>1)+speedY+0.5F)>>4) ||
		world->isBlockSolid((int)(x-(sizeX>>1)+0.5F)>>4,(int)(y+(sizeY>>1)+speedY-0.5F)>>4) ||
		world->isBlockSolid((int)(x+(sizeX>>1)-0.5F)>>4,(int)(y+(sizeY>>1)+speedY-0.5F)>>4))
	{
		OnCollide(app, world, gameUtility, speedX, speedY, YAxis);
		this->speedY = 0;
		speedY = 0;
		r = YAxis;
	}

	if (world->isBlockSolid((int)(x-(sizeX>>1)+speedX+0.5F)>>4,(int)(y-(sizeY>>1)+speedY+0.5F)>>4) ||
		world->isBlockSolid((int)(x+(sizeX>>1)+speedX-0.5F)>>4,(int)(y-(sizeY>>1)+speedY+0.5F)>>4) ||
		world->isBlockSolid((int)(x-(sizeX>>1)+speedX+0.5F)>>4,(int)(y+(sizeY>>1)+speedY-0.5F)>>4) ||
		world->isBlockSolid((int)(x+(sizeX>>1)+speedX-0.5F)>>4,(int)(y+(sizeY>>1)+speedY-0.5F)>>4))
	{
		OnCollide(app, world, gameUtility, speedX, speedY, XYAxis);
		if (abs(this->speedX) > abs(this->speedY))
		{
			this->speedX = 0;
			speedX = 0;
		}
		else
		{
			this->speedY = 0;
			speedY = 0;
		}

		CheckCollision(app, world, gameUtility, speedX, speedY);
		return XYAxis;
	}
	return r;
}

void Entity::OnCollide(App &app, World *world, GameUtility *gameUtility, float speedX, float speedY, CollisionType collisionType)
{
}

#ifdef CLIENT

void Entity::EventUpdate(App &app, const sf::Event &event, GameUtility* gameUtility)
{

}

void Entity::Draw(App &app, GameUtility *gameUtility)
{
	sf::Sprite *sprite = &(gameUtility->getTextureContainer().getTextures(spriteName)[spriteIndex]);
	if (sprite != nullptr)
	{
		if(	x + sizeX*0.5 >=
			(app.getView().getCenter().x - (app.getSize().x/2)) &&

			x - sizeX*0.5 <=
			(app.getView().getCenter().x + (app.getSize().x/2))&&

			y + sizeY*0.5 >=
			(app.getView().getCenter().y - (app.getSize().y/2)) &&

			y - sizeY*0.5 <= 
			(app.getView().getCenter().y + (app.getSize().y/2)))
		{
			sprite->setPosition(sf::Vector2f(x-(sizeX>>1), y-(sizeY>>1)));
			sprite->setRotation(angle);
			app.draw(*sprite);
		}
	}
	else
	{
		std::cout << "\"" << getTextureName() << "\" not found!" << std::endl;
	}
}
#endif

//void Entity::setPosition(float X, float Y) { x = X; y = Y; }
sf::Vector2f Entity::getPosition() { return(sf::Vector2f(x, y)); }

//void Entity::setX(float X) { x = X; }
//void Entity::setY(float Y) { y = Y; }
float Entity::getX() { return x; }
float Entity::getY() { return y; }

void Entity::setSize(float x, float y) { sizeX = x; sizeY = y; }
sf::Vector2f Entity::getSize() { return sf::Vector2f(sizeX, sizeY); }

void Entity::setAngle(float angle) {this->angle = angle; }
float Entity::getAngle() { return angle;  }
