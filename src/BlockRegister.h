#pragma once

#include <string>
#include <map>
#include <vector>
#include <functional>

class TextureContainer;
class Block;

class BlockRegister
{
	std::map<size_t, unsigned short> blockIdMap;
	std::vector<std::function<Block*(unsigned short)>> blockTypeList;
public:
	BlockRegister();
	void RegisterBlock(Block *block, size_t typeId);
	Block *getBlockType(unsigned short id, unsigned short metadata);
	unsigned short getBlockIdByTypeId(size_t typeId);
};