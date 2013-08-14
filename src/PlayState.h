#ifndef _SERVER
#pragma once
#include "App.h"
#include "gamestate.h"
#include <SFML\Graphics.hpp>

class World;
class InGameUI;
class Camera;
class EventHandler;
class NoobishBlockMenu;
class TextureContainer;
class Connection;

class PlayState : public GameState
{
	TextureContainer *tC;
	Camera *camera;
	NoobishBlockMenu *noobishBlockMenu;//InGameUI *blockMenu;
	Connection *connection;
	EventHandler *eventHandler;
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
