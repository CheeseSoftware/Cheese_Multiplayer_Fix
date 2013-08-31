#pragma once
#include "App.h"
#include "gamestate.h"

class World;
class Camera;
class TextureContainer;
class BlockRegister;

class SimulationState : public GameState
{
protected:
#ifndef _SERVER
	Camera *camera;
#endif
	TextureContainer *tC;
	BlockRegister *blockRegister; // surkod
	World *currentWorld;
public:
	SimulationState(App &app);
	~SimulationState();
    //virtual void EventUpdate(App &app, const sf::Event &event);
    //virtual GameState *Update(App &app);
    //virtual void Draw(App &app);
	inline World *getCurrentWorld();
	inline TextureContainer &getTextureContainer();
#ifndef _SERVER
	inline Camera &getCamera();
#endif
	inline BlockRegister &getBlockRegister();
};