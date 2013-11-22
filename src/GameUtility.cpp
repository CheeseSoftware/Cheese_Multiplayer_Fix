#include "GameUtility.h"
#include "Camera.h"
#include "World.h"
#include "TextureContainer.h"
#include "BlockRegister.h"

GameUtility::GameUtility(App &app)
{
#ifndef _SERVER
	camera = new Camera(2048);//setSpeed(8);
#endif
	tC = new TextureContainer();
	packetDataList = new std::queue<sf::Packet>();
	blockRegister = new BlockRegister();
	currentWorld = new World(this);
	
}
GameUtility::~GameUtility()
{

}

    //virtual void EventUpdate(App &app, const sf::Event &event);
    //virtual GameState *Update(App &app);
    //virtual void Draw(App &app);
/*World *GameUtility::getCurrentWorld()
{
	return currentWorld;
}

TextureContainer &GameUtility::getTextureContainer()
{
	return *tC;
}

BlockRegister &GameUtility::getBlockRegister()
{
	return *blockRegister;
}

#ifndef _SERVER
Camera &GameUtility::getCamera()
{
	return *camera;
}
#endif ppp........ -     */