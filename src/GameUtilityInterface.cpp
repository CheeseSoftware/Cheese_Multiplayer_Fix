#include "GameUtilityInterface.h"
#include "Camera.h"
#include "World.h"
#include "TextureContainer.h"

GameUtilityInterface::GameUtilityInterface(App &app)
{
#ifndef _SERVER
	camera = new Camera(8);//setSpeed(8);
	app.setView(*reinterpret_cast<sf::View*>(camera));
	currentWorld = new World();
	tC = new TextureContainer();
#endif
}
GameUtilityInterface::~GameUtilityInterface()
{

}

    //virtual void EventUpdate(App &app, const sf::Event &event);
    //virtual GameState *Update(App &app);
    //virtual void Draw(App &app);
/*World *GameUtilityInterface::getCurrentWorld()
{
	return currentWorld;
}

TextureContainer &GameUtilityInterface::getTextureContainer()
{
	return *tC;
}

BlockRegister &GameUtilityInterface::getBlockRegister()
{
	return *blockRegister;
}

#ifndef _SERVER
Camera &GameUtilityInterface::getCamera()
{
	return *camera;
}
#endif*/