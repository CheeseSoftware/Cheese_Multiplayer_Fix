#include <math.h>

#include "Block.h"
#include "Entity.h"
#include "EventHandler.h"
#include "TextureContainer.h"
#include "World.h"

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

#ifdef _SERVER
void Entity::Update(App &app, World *world, std::queue<sf::Packet> *packetDataList)
#else
void Entity::Update(App &app, World *world, std::queue<sf::Packet> *packetDataList, Camera *camera, EventHandler &EventHandler)
#endif
{
	float xFriction = friction;
	float yFriction = friction;

	std::pair<Block*, unsigned short> blockAndMetadata = world->getBlockAndMetadata((long)x+8>>4,(long)y+8>>4, 2);
	if (blockAndMetadata.first != nullptr)
		blockAndMetadata.first->OnEntityGravity(app, this, xFriction, yFriction, speedX, speedY, blockAndMetadata.second);

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
				if (CheckCollision(app, world, deltaX, deltaY))
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
			if (CheckCollision(app, world, (float)speedXNegativeFactor, (float)speedYNegativeFactor))
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
			if (CheckCollision(app, world, (float)speedXNegativeFactor, 0))
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
			if (CheckCollision(app, world, 0, (float)speedYNegativeFactor))
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
		CheckCollision(app, world, speedXModifier*speedXNegativeFactor, speedYModifier*speedYNegativeFactor);

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
		CheckCollision(app, world, speedX * app.getDeltaTime(), speedY * app.getDeltaTime());

		//x += speedX * app.getDeltaTime();
		//y += speedY * app.getDeltaTime();
				//std::cout << x << " " << y << std::endl;
		//< D:

		speedX *= 1 - tan(xFriction*M_PI/2) * app.getDeltaTime();
		speedY *= 1 - tan(yFriction*M_PI/2) * app.getDeltaTime();
	}
}

bool Entity::CheckCollision(App &app, World *world, float speedX, float speedY)
{
	bool r = false;

	if (speedX == 0 && speedY == 0)
		return false;

	if (world->isBlockSolid((int)(x+1+speedX)>>4,(int)(y+1)>>4) ||
		world->isBlockSolid((int)(x+14+speedX)>>4,(int)(y+1)>>4) ||
		world->isBlockSolid((int)(x+1+speedX)>>4,(int)(y+14)>>4) ||
		world->isBlockSolid((int)(x+14+speedX)>>4,(int)(y+14)>>4))
	{
		this->speedX = 0;
		speedX = 0;
		Collision(world);
		r = true;
	}

	if (world->isBlockSolid((int)(x+1)>>4,(int)(y+1+speedY)>>4) ||
		world->isBlockSolid((int)(x+14)>>4,(int)(y+1+speedY)>>4) ||
		world->isBlockSolid((int)(x+1)>>4,(int)(y+14+speedY)>>4) ||
		world->isBlockSolid((int)(x+14)>>4,(int)(y+14+speedY)>>4))
	{
		this->speedY = 0;
		speedY = 0;
		Collision(world);
		r = true;
	}

	if (world->isBlockSolid((int)(x+1+speedX)>>4,(int)(y+1+speedY)>>4) ||
		world->isBlockSolid((int)(x+14+speedX)>>4,(int)(y+1+speedY)>>4) ||
		world->isBlockSolid((int)(x+1+speedX)>>4,(int)(y+14+speedY)>>4) ||
		world->isBlockSolid((int)(x+14+speedX)>>4,(int)(y+14+speedY)>>4))
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

void Entity::EventUpdate(App &app, const sf::Event &event, World *world, std::queue<sf::Packet> *packetDataList)
{

}

void Entity::Draw(App &app, TextureContainer &tC)
{
	sf::Sprite *sprite = &(tC.getTextures(spriteName)[spriteIndex]);
	if (sprite != nullptr)
	{
		if ((int)x + app.getView().getCenter().x - (app.getSize().x>>1) <= 0)// &&
			//(int)y + app.getView().getCenter().y - (app.getSize().y>>1) >= 0 &&
			//(int)x + app.getView().getCenter().x + (app.getSize().x>>1) <= 0 &&
			//(int)x + app.getView().getCenter().x + (app.getSize().x>>1) <= 0)
		{
			sprite->setPosition(sf::Vector2f(x, y));
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

void Entity::setPosition(float X, float Y)
{
    x = X;
    y = Y;
}

sf::Vector2f Entity::getPosition() { return(sf::Vector2f(x, y)); }
void Entity::setX(float X) { x = X; }
void Entity::setY(float Y) { y = Y; }
float Entity::getX() { return x; }
float Entity::getY() { return y; }
sf::Vector2f Entity::getSize() { return sf::Vector2f(sizeX, sizeY); }
void Entity::setAngle(float angle) {this->angle = angle; }
float Entity::getAngle() { return angle;  }
