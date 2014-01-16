#ifndef _SERVER
#pragma once
#include "App.h"

class App;
class Entity;

class Camera : private sf::View
{
private:
	Entity *currentEntity;
	double speed;
public:
	//Camera();
	Camera(const double speed);
	Camera(const int speed);
	~Camera(void);
	void Update(App &app);
	void setCameraAt(Entity *entity);
	void setSpeed(const double speed);
	void setSpeed(const int speed);
	void setZoom(float zoom) { sf::View::zoom(zoom); };
	sf::Vector2f getEntityPosition();
	Entity *Camera::getEntity();
	double getLeftX();
	double getTopY();
	double getRightX();
	double getButtomY();
};

/*inline Camera& GetCamera(App &app)
{
	return (*const_cast<Camera*>(reinterpret_cast<const Camera*>(&app.getView())));
}*/
#endif

//#define app.getView() (*const_cast<Camera*>(reinterpret_cast<const Camera*>(&app.GetView())))