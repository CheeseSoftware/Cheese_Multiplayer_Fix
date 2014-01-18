#ifndef _SERVER
#include <math.h>

#include "Camera.h"
#include "Entity.h"
#include "Game.h"

/*Camera::Camera() : View(sf::FloatRect(200, 200, 300, 200))
{
	setSize(1152,720);
}*/

Camera::Camera(double speed) : View(sf::FloatRect(200, 200, 300, 200))
{
	this->speed = speed;
	currentEntity = nullptr;

	setSize(1152,720);// temporära magiska nummer
}

Camera::Camera(int speed) : View(sf::FloatRect(200, 200, 300, 200))
{
	this->speed = 1.f - 1.f/(float)speed;
	currentEntity = nullptr;

	setSize(1152,720);// temporära magiska nummer
}


Camera::~Camera(void)
{

}

void Camera::Update(App &app, Game &game)
{
	if (currentEntity != nullptr)
	{
		const float deltaX = currentEntity->getX()+8-getCenter().x;
		const float deltaY = currentEntity->getY()+8-getCenter().y;
		float speedFactor = 1.f-pow(1.f-speed, app.getDeltaTime());//atan(app.getDeltaTime()*speed)*2/3.14159265358979323846264338327950288419;

		//speedFactor = (speedFactor > 1.f)? 1.f : speedFactor;
		const float distance = sqrt(pow(deltaX, 2) + pow(deltaY, 2));

		if ( distance > 100)
		{
			const float temp = (distance-100) / distance;
			speedFactor = (temp > speedFactor)? temp : speedFactor;
		}

		move(deltaX*speedFactor,deltaY*speedFactor);
	}
}

void Camera::setCameraAt(Entity *entity)
{
	if (currentEntity != entity)
		currentEntity = entity;
}

void Camera::setSpeed(double speed)
{
	this->speed = speed;
}

void Camera::setSpeed(int speed)
{
	this->speed = 1.f - 1.f/(float)speed;
}

sf::Vector2f Camera::getEntityPosition()
{
	if(currentEntity != nullptr)
		return(currentEntity->getPosition());
	else
		return(sf::Vector2f(0, 0));
}

Entity *Camera::getEntity() { return currentEntity; }

double Camera::getLeftX()
{
	return getCenter().x - getSize().x/2;
}
double Camera::getTopY()
{
	return getCenter().y - getSize().y/2;
}
double Camera::getRightX()
{
	return getCenter().x + getSize().x/2;
}
double Camera::getButtomY()
{
	return getCenter().y + getSize().y/2;
}

#endif