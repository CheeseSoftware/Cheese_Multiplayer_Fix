#ifndef _SERVER
#pragma once
#include "App.h"
#include "GameUtility.h"
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
//template<class T> class EventHandler;
class NoobishBlockMenu;
class TextureContainer;
class Connection;
class BlockRegister;

class PlayState : public GameUtility
{
	//TextureContainer *tC;
	//Camera *camera;
	NoobishBlockMenu *noobishBlockMenu;//InGameUI *blockMenu;
	Connection *connection;
	EventHandler<GameUtility*> eventHandler;
    sf::Clock fpsClock;
	//BlockRegister *blockRegister; // surkod
	//World *currentWorld;
	void ProcessPackets(GameUtility *gameUtility);
public:
	PlayState(App &app);
	~PlayState();
    virtual void EventUpdate(App &app, const sf::Event &event);
    virtual GameState *Update(App &app);
    virtual void Draw(App &app);
};
#endif
