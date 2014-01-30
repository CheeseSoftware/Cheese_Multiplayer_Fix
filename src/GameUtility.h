#pragma once
#include "App.h"
#include "GameState.h"
#include "World.h"
#include "SoundHandler.h"

class World;
class Camera;
class TextureContainer;
class BlockRegister;

class GameUtility : public virtual GameState
{
protected:
#ifdef CLIENT
	Camera *camera;
#endif
	TextureContainer *tC;
	BlockRegister *blockRegister; // surkod
	World *currentWorld;
	std::queue<sf::Packet> *packetDataList;
	//SoundHandler soundHandler;
public:
	GameUtility(App &app);
	~GameUtility();
	//virtual void EventUpdate(App &app, Game &game, const sf::Event &event);
	//virtual GameState *Update(App &app, Game &game);
	//virtual void Draw(App &app);
	inline World *getCurrentWorld() { return currentWorld; }
	inline TextureContainer &getTextureContainer() { return *tC; }
	//inline SoundHandler &getSoundHandler() { return soundHandler; }
	inline std::queue<sf::Packet>* getPacketDataList() { return packetDataList; };
	inline void SendPacket(sf::Packet p) { packetDataList->push(p); };
#ifdef CLIENT
	inline Camera &getCamera() { return *camera; }
#endif
	inline BlockRegister &getBlockRegister() { return *blockRegister; }
};