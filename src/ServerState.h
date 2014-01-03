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

class ServerState : public GameUtility
{
	ServerConnection* sC;
	void ProcessPackets(GameUtility *gameUtility);
public:
	ServerState(App &app);
	~ServerState();
	virtual void EventUpdate(App &app, Game &game, const sf::Event &event) {}
    virtual GameState *Update(App &app, Game &game);
	virtual void Draw(App &app) {}
};
#endif