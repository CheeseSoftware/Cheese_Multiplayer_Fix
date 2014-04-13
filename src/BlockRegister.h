#pragma once

#include <string>
#include <map>
#include <vector>
#include <functional>

class ITextureContainer;
class Block;
namespace sf { class Sprite; }

class BlockRegister
{
	std::map<size_t, unsigned short> blockIdMap;
	std::vector<Block*> blockList;
	std::vector<std::function<Block*(unsigned short)>> blockTypeList;
	std::vector<sf::Sprite**> blockTextureList;
public:
	BlockRegister();
	void RegisterBlock(Block *block, const size_t typeId);
#ifdef CLIENT
	void RegisterBlockTextures(ITextureContainer *Tc);
#endif
	Block *getBlockType(const unsigned short id);
#ifdef CLIENT
	sf::Sprite **getBlockTextures(const Block *block);
#endif
	unsigned short getBlockIdByTypeId(const size_t typeId);
};