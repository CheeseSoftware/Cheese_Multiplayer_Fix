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
class GameUtilityInterface;

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
	//long chunkMatrixCenterRow;
	//std::pair<std::deque<std::pair<std::deque<Chunk*>,long>>,long> chunkMatrix;
	std::map<unsigned short, std::function<Block*(unsigned short)>> blockTypeMap;
	std::vector<Entity*> entityList;
	std::map<short, Player*> playerList;
	std::map<std::pair<short,short>,Block*> BlockMap;
	std::pair<std::tuple<long, long, unsigned short>, std::pair<Block*, unsigned short>*> lastBlock;
#ifndef _SERVER
	EventHandler eventHandler;
#endif
public:
	World();
#ifndef _SERVER
	void EventUpdate(App &app, const sf::Event &event, GameUtilityInterface* gameUtilityInterface);
	void Draw(App &app, TextureContainer &tC);
#endif

	void Update(App &app, GameUtilityInterface *GameUtilityInterface);
	void RegisterBlock(unsigned short key, std::function<Block*(unsigned short)> value);
	void setBlock(long x, long y, long layer, unsigned short id, GameUtilityInterface *gameUtilityInterface);
	void setBlockAndMetadata(long x, long y, long layer, unsigned short id, unsigned short metadata, GameUtilityInterface *gameUtilityInterface);
	void setBlockMetadata(long x, long y, long layer, unsigned short metadata, GameUtilityInterface *gameUtilityInterface);
	MessageType setBlockAndMetadataClientOnly(long x, long y, long layer, unsigned short id, unsigned short metadata, GameUtilityInterface *gameUtilityInterface);
	MessageType setBlockMetadataClientOnly(long x, long y, long layer, unsigned short metadata, GameUtilityInterface *gameUtilityInterface);
	Block *getBlock(long x, long y, long layer);
	std::pair<Block*, unsigned short> getBlockAndMetadata(long x, long y, long layer);
	void Expand(long x, long y, Chunk* chunk);
	void AddBlockType(unsigned short, std::function<Block*(unsigned short)>);
	bool isBlockSolid(long x, long y);
	Block *getBlockType(unsigned short id, unsigned short metadata);
	std::map<unsigned short, std::function<Block*(unsigned short)>>& getBlockTypeMap();
	int AddEntity(Entity*);
	void RemoveEntity(int id);
	int AddPlayer(int id, Player*);
	void RemovePlayer(int id);
	Player* GetPlayer(int id);
	void SetPlayer(int id, Player *player);
};