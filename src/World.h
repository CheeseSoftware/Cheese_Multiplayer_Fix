#pragma once

#include <functional>
#include <vector>
#include <map>
#include <list>
#include <deque>
#include <queue>
#include <tuple>
#include <mutex>
#include "App.h"
#include <SFML\Network.hpp>
#include "EventHandler.h"
#include "Generator.h"

class Entity;
class Player;
class Creature;
class Block;
class Chunk;
class TextureContainer;
class Camera;
//template<class T> class EventHandler;
class GameState;
class GameUtility;
class BlockRegister;

enum MessageType;

#define ChunkWidthHeight 256

/*struct Chunk
{
	Block *blocks[256][256];
};*/

typedef	std::pair<std::deque<Chunk*>, long> ChunkColumnType;
typedef std::pair<std::deque<ChunkColumnType>,long> ChunkMatrixType; // deque(y)<pair<deque<chunk>(x)>,long(chunkCenterY)>


class World
{
private:
	short int sizeX;
	short int sizeY;
	ChunkMatrixType chunkMatrix;
	std::mutex chunkMatrixLock;
	std::vector<Entity*> entityList;
	std::mutex entityListLock;
	std::map<short, Creature*> creatureList;
	std::mutex creatureListLock;
	//std::map<std::pair<short,short>,Block*> BlockMap;
	std::pair<std::tuple<long, long, unsigned short>, std::pair<Block*, unsigned short>*> lastBlock;
	std::pair<Block*, unsigned short> physicBlock;
	StandardGenerator generator;
#ifndef _SERVER
	EventHandler<GameUtility*> eventHandler;
#endif
public:
	World(GameUtility *gameUtility);
#ifndef _SERVER
	void EventUpdate(App &app, const sf::Event &event, GameUtility* gameUtility);
	void Draw(App &app, GameUtility *gameUtility);
#endif

	void Update(App &app, GameUtility *GameUtility);
	void setBlock(long x, long y, long layer, unsigned short id, GameUtility *gameUtility);
	void setBlockAndMetadata(long x, long y, long layer, unsigned short id, unsigned short metadata, GameUtility *gameUtility);
	void setBlockMetadata(long x, long y, long layer, unsigned short metadata, GameUtility *gameUtility);
	void SendSetBlockAndMetadata(long x, long y, long layer, unsigned short id, unsigned short metadata, GameUtility *gameUtility);
	MessageType setBlockAndMetadataLocal(long x, long y, long layer, unsigned short id, unsigned short metadata, GameUtility *gameUtility);
	MessageType setBlockMetadataLocal(long x, long y, long layer, unsigned short metadata, GameUtility *gameUtility);
	MessageType getBlockPacket(long x, long y, long layer, unsigned short id, unsigned short metadata, GameUtility *gameUtility);
	Block *getBlock(long x, long y, long layer);
	std::pair<Block*, unsigned short> getBlockAndMetadata(long x, long y, long layer);
	const std::pair<Block*, unsigned short> getPhysicBlock() const;
	void Expand(long x, long y, Chunk* chunk);
	bool isBlockSolid(long x, long y);
	int AddEntity(Entity*);
	void RemoveEntity(int id);
	int AddCreature(int id, Creature *creature);
	void RemoveCreature(int id);
	Creature* getCreature(int id);
	void SetCreature(int id, Creature *creature);
	Chunk *getChunk(long x, long y);
	Chunk *getGenerateChunk(long x, long y, GameUtility *gameUtility);
};