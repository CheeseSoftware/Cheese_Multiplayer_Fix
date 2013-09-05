#ifdef _SERVER
#pragma once
#include "GameUtility.h"
#include "GameState.h"
#include "TextureContainer.h"
#include "ServerConnection.h"
#include "Player.h"
#include "App.h"

class World;
class InGameUI;
class Camera;

class ServerState : public GameState, public GameUtility
{
	ServerConnection* sC;
	void ProcessPackets();
public:
	ServerState(App &app);
	~ServerState();
	virtual void EventUpdate(App &app, const sf::Event &event) {}
    virtual GameState *Update(App &app);
	virtual void Draw(App &app) {}
};
#endif