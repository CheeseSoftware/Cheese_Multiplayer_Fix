#ifndef _SERVER
#pragma once
#include "App.h"
#include "GameUtilityInterface.h"
#include "GameState.h"
//#include "BlockRegister.h"
//#include "TextureContainer.h"
//#include "NoobishBlockMenu.h"
//#include "Connection.h"
#include "EventHandler.h"
#include <SFML\Graphics.hpp>

class World;
class InGameUI;
class Camera;
class EventHandler;
class NoobishBlockMenu;
class TextureContainer;
class Connection;
class BlockRegister;

class PlayState : public GameState, public GameUtilityInterface
{
	//TextureContainer *tC;
	//Camera *camera;
	NoobishBlockMenu *noobishBlockMenu;//InGameUI *blockMenu;
	Connection *connection;
	EventHandler eventHandler;
    sf::Clock fpsClock;
	//BlockRegister *blockRegister; // surkod
	//World *currentWorld;
	void ProcessPackets();
public:
	PlayState(App &app);
	~PlayState();
    virtual void EventUpdate(App &app, const sf::Event &event);
    virtual GameState *Update(App &app);
    virtual void Draw(App &app);
};
#endif
