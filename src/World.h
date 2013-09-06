#pragma once

#include <functional>
#include <vector>
#include <map>
#include <list>
#include <deque>
#include <queue>
#include <tuple>
#include "App.h"
#include <SFML\Network.hpp>
#include "EventHandler.h"

class Entity;
class Player;
class Block;
class Chunk;
class TextureContainer;
class Camera;
class EventHandler;
class GameUtility;

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
	std::vector<Entity*> entityList;
	std::map<short, Player*> playerList;
	//std::map<std::pair<short,short>,Block*> BlockMap;
	std::pair<std::tuple<long, long, unsigned short>, std::pair<Block*, unsigned short>*> lastBlock;
#ifndef _SERVER
	EventHandler eventHandler;
#endif
public:
	World();
#ifndef _SERVER
	void EventUpdate(App &app, const sf::Event &event, GameUtility* gameUtility);
	void Draw(App &app, GameUtility *gameUtility);
#endif

	void Update(App &app, GameUtility *GameUtility);
	void setBlock(long x, long y, long layer, unsigned short id, GameUtility *gameUtility);
	void setBlockAndMetadata(long x, long y, long layer, unsigned short id, unsigned short metadata, GameUtility *gameUtility);
	void setBlockMetadata(long x, long y, long layer, unsigned short metadata, GameUtility *gameUtility);
	MessageType setBlockAndMetadataClientOnly(long x, long y, long layer, unsigned short id, unsigned short metadata, GameUtility *gameUtility);
	MessageType setBlockMetadataClientOnly(long x, long y, long layer, unsigned short metadata, GameUtility *gameUtility);
	Block *getBlock(long x, long y, long layer);
	std::pair<Block*, unsigned short> getBlockAndMetadata(long x, long y, long layer);
	void Expand(long x, long y, Chunk* chunk);
	bool isBlockSolid(long x, long y);
	int AddEntity(Entity*);
	void RemoveEntity(int id);
	int AddPlayer(int id, Player*);
	void RemovePlayer(int id);
	Player* GetPlayer(int id);
	void SetPlayer(int id, Player *player);
};