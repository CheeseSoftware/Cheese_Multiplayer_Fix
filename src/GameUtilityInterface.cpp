#include "GameUtilityInterface.h"
#include "Camera.h"
#include "World.h"
#include "TextureContainer.h"
#include "BlockRegister.h"

GameUtilityInterface::GameUtilityInterface(App &app)
{
#ifndef _SERVER
	camera = new Camera(8);//setSpeed(8);
	app.setView(*reinterpret_cast<sf::View*>(camera));
#endif
	tC = new TextureContainer();
	currentWorld = new World();
	packetDataList = new std::queue<sf::Packet>();
	blockRegister = new BlockRegister();
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