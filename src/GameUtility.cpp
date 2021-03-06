#include "GameUtility.h"
#include "Camera.h"
#include "World.h"
#include "TextureContainer.h"
#include "BlockRegister.h"

GameUtility::GameUtility(App &app)
{
#ifdef CLIENT
	camera = new Camera(1024);//setSpeed(8);
#endif
	//tC = new TextureContainer();
	packetDataList = new std::queue<sf::Packet>();
	blockRegister = new BlockRegister();
	currentWorld = new World(this);
	
}
GameUtility::~GameUtility()
{

}

    //virtual void EventUpdate(App &app, Game *game, const sf::Event &event);
    //virtual GameState *Update(App &app, Game *game);
    //virtual void Draw(App &app, Game *game);
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

#ifdef CLIENT
Camera &GameUtility::getCamera()
{
	return *camera;
}
#endif ppp........ -     */