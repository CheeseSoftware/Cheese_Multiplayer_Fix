#include <math.h>

#include "Block.h"
#include "Entity.h"
#include "EventHandler.h"
#include "TextureContainer.h"
#include "World.h"
#include "GameUtility.h"

Entity::Entity(float x, float y, short sizeX, short sizeY,
			   float angle, float speed, float friction, std::string spriteName,
			   int spriteIndex, bool isClientControlling)
{
	this->x = x;
	this->y = y;
	this->speed = speed;
	this->friction = friction;
	this->isClientControlling = isClientControlling;

	speedX = 0;
	speedY = 0;
	this->sizeX = sizeX;
	this->sizeY = sizeY;

	this->angle = angle;
	this->spriteName = spriteName;
	this->spriteIndex = spriteIndex;
}

void Entity::PhysicUpdate(World *world, float timeSpan)
{

}

/*#ifdef _SERVER
void Entity::Update(App &app, World *world, std::queue<sf::Packet> *packetDataList)
#else
void Entity::Update(App &app, World *world, std::queue<sf::Packet> *packetDataList, Camera *camera, EventHandler &EventHandler)
#endif*/
void Entity::Update(App &app, GameUtility *GameUtility)
{
	float xFriction = friction;
	float yFriction = friction;

	std::pair<Block*, unsigned short> blockAndMetadata = GameUtility->getCurrentWorld()->getBlockAndMetadata(
		(long)x>>4L,
		(long)y>>4L,
		2);

	if (blockAndMetadata.first != nullptr)
		blockAndMetadata.first->OnEntityHover(app, this, xFriction, yFriction, speedX, speedY, blockAndMetadata.second);
	//(app, this, xFriction, yFriction, speedX, speedY, blockAndMetadata.second);

	if (speedX != 0.0F || speedY != 0.0F)
	{


		float speedXModifier = abs(speedX * app.getDeltaTime());

		float speedYModifier = abs(speedY * app.getDeltaTime());


		//float speedModifier = speedX * app.getDeltaTime();

		//float speedYModifier = abs(speedY * app.getDeltaTime());

		char speedXNegativeFactor = (speedX > 0)? 1:-1;
		char speedYNegativeFactor = (speedY > 0)? 1:-1;


		//NEW FAILED PHYSICS D:  {
		//double speed = sqrt(pow(abs(speedX)*app.getDeltaTime(),2)+pow(abs(speedY)*app.getDeltaTime(),2));

		//<<<<<<< HEAD
		double speed = sqrt(pow(speedX*app.getDeltaTime(),2)+pow(speedY*app.getDeltaTime(),2));

		//=======
		double angle = atan2(speedY, speedX);
		//>>>>>>> 2dbb0fccc9120629075f0f104405e4486369d95b

		double deltaX = cos(angle);
		double deltaY = sin(angle);

		for (int i = 0; i < 2; i++)
		{
			while(speed >= 1)
			{
				if (CheckCollision(app, GameUtility->getCurrentWorld(), deltaX, deltaY))
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

		/*if (CheckCollision(app, world, deltaX*speed, deltaY*speed))
		{
		x += deltaX*speed;
		y += deltaY*speed;
		}*/

		while (speedXModifier >= 1 && speedYModifier >= 1)
		{
			if (CheckCollision(app, GameUtility->getCurrentWorld(), (float)speedXNegativeFactor, (float)speedYNegativeFactor))
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
			if (CheckCollision(app, GameUtility->getCurrentWorld(), (float)speedXNegativeFactor, 0))
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
			if (CheckCollision(app, GameUtility->getCurrentWorld(), 0, (float)speedYNegativeFactor))
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

		//if (!CheckCollision(app, world, speedXModifier*speedXNegativeFactor, speedYModifier*speedYNegativeFactor))
		//{
		//x += speedXModifier*speedXNegativeFactor;
		//y += speedYModifier*speedYNegativeFactor;
		//}
		//else
		//{
		CheckCollision(app, GameUtility->getCurrentWorld(), speedXModifier*speedXNegativeFactor, speedYModifier*speedYNegativeFactor);

		if (speedX != 0)
			x += speedXModifier*speedXNegativeFactor;

		if (speedY != 0)
			y += speedYModifier*speedYNegativeFactor;


		/*if (speedX != 0)
		x += speedXModifier*speedXNegativeFactor;

		if (speedY != 0)
		y += speedYModifier*speedYNegativeFactor;*/
		//}

		// } D: 

		//> gammal fysikD:
		CheckCollision(app, GameUtility->getCurrentWorld(), speedX * app.getDeltaTime(), speedY * app.getDeltaTime());

		//x += speedX * app.getDeltaTime();
		//y += speedY * app.getDeltaTime();
		//std::cout << x << " " << y << std::endl;
		//< D:

		std::cout << "speedX(a): " << speedX << std::endl;
		speedX *= 1.0-xFriction*app.getDeltaTime();//pow(1-xFriction, app.getDeltaTime());//tan(xFriction*M_PI/2) * app.getDeltaTime();
		speedY *= 1.0-yFriction*app.getDeltaTime();//pow(1-yFriction, app.getDeltaTime());//tan(yFriction*M_PI/2) * app.getDeltaTime();
		std::cout << "speedX(b): " << speedX << std::endl;
	}
}

bool Entity::CheckCollision(App &app, World *world, float speedX, float speedY)
{
	bool r = false;

	if (speedX == 0 && speedY == 0)
		return false;

	if (world->isBlockSolid((int)(x-(sizeX>>1)+speedX+0.5F)>>4,(int)(y-(sizeY>>1)+0.5F)>>4) ||
		world->isBlockSolid((int)(x+(sizeX>>1)+speedX-0.5F)>>4,(int)(y-(sizeY>>1)+0.5F)>>4) ||
		world->isBlockSolid((int)(x-(sizeX>>1)+speedX+0.5F)>>4,(int)(y+(sizeY>>1)-0.5F)>>4) ||
		world->isBlockSolid((int)(x+(sizeX>>1)+speedX-0.5F)>>4,(int)(y+(sizeY>>1)-0.5F)>>4))
	{
		this->speedX = 0;
		speedX = 0;
		Collision(world);
		r = true;
	}

	if (world->isBlockSolid((int)(x-(sizeX>>1)+0.5F)>>4,(int)(y-(sizeY>>1)+speedY+0.5F)>>4) ||
		world->isBlockSolid((int)(x+(sizeX>>1)-0.5F)>>4,(int)(y-(sizeY>>1)+speedY+0.5F)>>4) ||
		world->isBlockSolid((int)(x-(sizeX>>1)+0.5F)>>4,(int)(y+(sizeY>>1)+speedY-0.5F)>>4) ||
		world->isBlockSolid((int)(x+(sizeX>>1)-0.5F)>>4,(int)(y+(sizeY>>1)+speedY-0.5F)>>4))
	{
		this->speedY = 0;
		speedY = 0;
		Collision(world);
		r = true;
	}

	if (world->isBlockSolid((int)(x-(sizeX>>1)+speedX+0.5F)>>4,(int)(y-(sizeY>>1)+speedY+0.5F)>>4) ||
		world->isBlockSolid((int)(x+(sizeX>>1)+speedX-0.5F)>>4,(int)(y-(sizeY>>1)+speedY+0.5F)>>4) ||
		world->isBlockSolid((int)(x-(sizeX>>1)+speedX+0.5F)>>4,(int)(y+(sizeY>>1)+speedY-0.5F)>>4) ||
		world->isBlockSolid((int)(x+(sizeX>>1)+speedX-0.5F)>>4,(int)(y+(sizeY>>1)+speedY-0.5F)>>4))
	{
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

		CheckCollision(app, world, speedX, speedY);
		Collision(world);
		return true;
	}
	return r;

	/*bool solid[2][2] = {{
	world->isBlockSolid((int)(x)>>4,(int)(y)>>4),
	world->isBlockSolid((int)(x+15)>>4,(int)(y)>>4)},{
	world->isBlockSolid((int)(x)>>4,(int)(y+16)>>4),
	world->isBlockSolid((int)(x+15)>>4,(int)(y+16)>>4)}};

	if (!solid[0][0] || !solid[1][0] || !solid[0][1] || !solid[1][1])
	{
	if (abs(speedX) > abs(speedY))
	{
	if (speedX > 0 && (solid[1][0] || solid[1][1]))//if (solid[0][0] || solid[1][0] || solid[0][1] || solid[1][1])
	{
	FixateX();

	if (speedY > 0 && solid[1][1])//if (solid[0][0] || solid[1][0] || solid[0][1] || solid[1][1])
	FixateY();
	else if (solid[1][0])
	FixateY();
	}
	else if (solid[0][0] || solid[0][1])
	{
	FixateX();

	if (speedY > 0 && solid[0][1])//if (solid[0][0] || solid[1][0] || solid[0][1] || solid[1][1])
	FixateY();
	else if (solid[0][0])
	FixateY();
	}
	}
	else
	{
	if (speedY > 0 && (solid[0][1] || solid[1][1]))//if (solid[0][0] || solid[1][0] || solid[0][1] || solid[1][1])
	{
	FixateY();

	if (speedX > 0 && solid[1][1])//if (solid[0][0] || solid[1][0] || solid[0][1] || solid[1][1])
	FixateX();
	else if (solid[0][1])
	FixateX();
	}
	else if (solid[0][0] || solid[1][0])
	{
	FixateY();

	if (speedX > 0 && solid[1][0])//if (solid[0][0] || solid[1][0] || solid[0][1] || solid[1][1])
	FixateX();
	else if (solid[0][0])
	FixateX();
	}
	}
	}*/
}

void Entity::Collision(World *world)
{
}

/*void Entity::FixateX()
{
if (speedX > 0)
{
x = (int)x+4>>4<<4;
}
else
{
x = (int)(x+12)>>4<<4;
}
speedX = 0;
}

void Entity::FixateY()
{
if (speedY > 0)
{
y = (int)y+4>>4<<4;
}
else
{
y = (int)(y+12)>>4<<4;
}
speedY = 0;
}*/

#ifndef _SERVER

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

void Entity::setPosition(float X, float Y) { x = X; y = Y; }
sf::Vector2f Entity::getPosition() { return(sf::Vector2f(x, y)); }

void Entity::setX(float X) { x = X; }
void Entity::setY(float Y) { y = Y; }
float Entity::getX() { return x; }
float Entity::getY() { return y; }

void Entity::setSize(float x, float y) { sizeX = x; sizeY = y; }
sf::Vector2f Entity::getSize() { return sf::Vector2f(sizeX, sizeY); }

void Entity::setAngle(float angle) {this->angle = angle; }
float Entity::getAngle() { return angle;  }
