#include "GameUtility.h"
#include "Camera.h"
#include "World.h"
#include "TextureContainer.h"
#include "BlockRegister.h"

GameUtility::GameUtility(App &app)
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
#endif*/