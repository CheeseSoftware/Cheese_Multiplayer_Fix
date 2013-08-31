#include "SimulationState.h"
#include "Camera.h"
#include "World.h"
#include "TextureContainer.h"

SimulationState::SimulationState(App &app)
{
#ifndef _SERVER
	camera = new Camera(8);//setSpeed(8);
	app.setView(*reinterpret_cast<sf::View*>(camera));
	currentWorld = new World();
	tC = new TextureContainer();
#endif
}
SimulationState::~SimulationState()
{

}

    //virtual void EventUpdate(App &app, const sf::Event &event);
    //virtual GameState *Update(App &app);
    //virtual void Draw(App &app);
World *SimulationState::getCurrentWorld()
{
	return currentWorld;
}

TextureContainer &SimulationState::getTextureContainer()
{
	return *tC;
}

BlockRegister &SimulationState::getBlockRegister()
{
	return *blockRegister;
}

#ifndef _SERVER
Camera &SimulationState::getCamera()
{
	return *camera;
}
#endif