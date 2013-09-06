#pragma once

#include <string>
#include <map>
#include <vector>
#include <functional>

class TextureContainer;
class Block;
namespace sf { class Sprite; }

class BlockRegister
{
	std::map<size_t, unsigned short> blockIdMap;
	std::vector<Block*> blockList;
	std::vector<std::function<Block*(unsigned short)>> blockTypeList;
	std::vector<sf::Sprite*> blockTextureList;
public:
	BlockRegister();
	void RegisterBlock(Block *block, size_t typeId);
#ifndef _SERVER
	void RegisterBlockTextures(TextureContainer &Tc);
#endif
	Block *getBlockType(unsigned short id);
#ifndef _SERVER
	sf::Sprite *getBlockTextures(Block *block);
#endif
	unsigned short getBlockIdByTypeId(size_t typeId);
};