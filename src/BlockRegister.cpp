#include "BlockRegister.h"
#include "TextureContainer.h"
#include "Block.h"
#include "BlockSolid.h"
#include "BlockBackground.h"
#include "BlockGravity.h"
#include "BlockChest.h"
#include <typeinfo>
#include <iostream>


BlockRegister::BlockRegister()
{
	std::cout << this << std::endl;
	//RegisterBlock(nullptr, 0);
	unsigned short i;
	blockTypeList.push_back(nullptr);
	RegisterBlock(new BlockSolid(i), typeid(BlockSolid).hash_code()); i++;
	RegisterBlock(new BlockBackground(i), typeid(BlockBackground).hash_code()); i++;
	RegisterBlock(new BlockGravity(i), typeid(BlockGravity).hash_code()); i++;
	RegisterBlock(new BlockChest(i), typeid(BlockChest).hash_code()); i++;
}

void BlockRegister::RegisterBlock(Block *block, size_t typeId)
{
	std::cout << blockTypeList.size() << std::endl;
	blockIdMap.emplace(typeId, blockTypeList.size());
	blockTypeList.push_back(block->RegisterBlock(blockTypeList.size()));
}

#ifndef _SERVER
	void RegisterBlockTextures(TextureContainer &Tc)
	{

	}
#endif

Block *BlockRegister::getBlockType(unsigned short id, unsigned short metadata)
{
	if (id == 0)
		return nullptr;
	return (id >= blockTypeList.size())? nullptr : blockTypeList[id](metadata);
}

unsigned short BlockRegister::getBlockIdByTypeId(size_t typeId)
{
	auto it = blockIdMap.find(typeId);//blockIdMapfind(typeId);
	std::cout << it->second << " " << typeId << std::endl;
	return (it == blockIdMap.end()) ? 0 : it->second;
}