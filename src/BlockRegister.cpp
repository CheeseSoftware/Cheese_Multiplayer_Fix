#include "BlockRegister.h"
#include "TextureContainer.h"
#include "Block.h"
#include "BlockSolid.h"
#include "BlockBackground.h"
#include "BlockGravity.h"
#include <typeinfo>
#include <iostream>

BlockRegister::BlockRegister()
{
	std::cout << this << std::endl;
	unsigned short i = 1;
	//RegisterBlock(nullptr, 0);
	blockTypeList.push_back(nullptr);
	RegisterBlock(new BlockSolid(i), typeid(BlockSolid).hash_code()); i++;
	RegisterBlock(new BlockBackground(i), typeid(BlockBackground).hash_code()); i++;
	RegisterBlock(new BlockGravity(i), typeid(BlockGravity).hash_code()); i++;
}

void BlockRegister::RegisterBlock(Block *block, size_t typeId)
{
	std::cout << blockTypeList.size() << std::endl;
	blockIdMap.emplace(typeId, blockTypeList.size());
	blockTypeList.push_back(block->RegisterBlock(blockTypeList.size()));
}

Block *BlockRegister::getBlockType(unsigned short id, unsigned short metadata)
{
	return (id >= blockTypeList.size())? nullptr : blockTypeList[id](metadata);
}

unsigned short BlockRegister::getBlockIdByTypeId(size_t typeId, unsigned short metadata)
{
	auto it = blockIdMap.find(typeId);//blockIdMapfind(typeId);
	return (it == blockIdMap.end()) ? 0 : it->second;
}