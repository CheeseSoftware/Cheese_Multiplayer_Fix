#ifndef _SERVER
#include "Camera.h"
#include "Entity.h"

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


Camera::~Camera(void)
{

}

void Camera::Update(App &app)
{
	if (currentEntity != nullptr)
	{
		float deltaX = currentEntity->getX()+8-getCenter().x;
		float deltaY = currentEntity->getY()+8-getCenter().y;
		float speedFactor = atan(app.getDeltaTime()*speed)*2/3.14159265358979323846264338327950288419F;

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