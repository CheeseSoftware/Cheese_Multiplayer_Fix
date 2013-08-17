#pragma once

#include <string>
#include <map>
#include <functional>

class TextureContainer;
class Block;

class BlockRegister
{
	std::map<size_t, std::function<Block*(unsigned short)>> blockTypeList;
public:
	BlockRegister();
	void RegisterBlock(TextureContainer tC, Block *block, size_t typeId);
	Block *getBlockType(unsigned short id, unsigned short metadata);
	Block *getBlockTypeByTypeId(size_t typeId, unsigned short metadata);
};