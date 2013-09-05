#pragma once
#include "App.h"
#include "BlockRegister.h"
#include "World.h"
#include "TextureContainer.h"
#include "Camera.h"

class World;
class Camera;
class TextureContainer;
class BlockRegister;

class GameUtility
{
protected:
#ifndef _SERVER
	Camera *camera;
#endif
	TextureContainer *tC;
	BlockRegister *blockRegister; // surkod
	World *currentWorld;
	std::queue<sf::Packet> *packetDataList;
public:
	GameUtility(App &app);
	~GameUtility();
	//virtual void EventUpdate(App &app, const sf::Event &event);
	//virtual GameState *Update(App &app);
	//virtual void Draw(App &app);
	inline World *getCurrentWorld() { return currentWorld; }
	inline TextureContainer &getTextureContainer() { return *tC; }
	inline std::queue<sf::Packet>* getPacketDataList() { return packetDataList; };
	inline void SendPacket(sf::Packet p) { packetDataList->push(p); };
#ifndef _SERVER
	inline Camera &getCamera() { return *camera; }
#endif
	inline BlockRegister &getBlockRegister() { return *blockRegister; }
};