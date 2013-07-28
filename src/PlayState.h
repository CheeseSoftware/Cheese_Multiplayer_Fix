#ifndef _SERVER
#pragma once
#include "App.h"
#include "gamestate.h"
#include "TextureContainer.h"
#include "Connection.h"
#include <SFML\Graphics.hpp>

class World;
class InGameUI;
class Camera;
class EventHandler;

class PlayState : public GameState
{
	TextureContainer tC;
	Camera *camera;
	InGameUI *blockMenu;
	Connection *connection;
	EventHandler eventHandler;
	void ProcessPackets();
public:
	PlayState(App &app);
	~PlayState();
    virtual void EventUpdate(App &app, const sf::Event &event);
    virtual GameState *Update(App &app);
    virtual void Draw(App &app);
	World* currentWorld;
};
#endif
