#include "BlockRegister.h"
#include "TextureContainer.h"
#include "Block.h"
#include "BlockSolid.h"
#include "BlockBackground.h"
#include "BlockGravity.h"
#include "BlockChest.h"
#include "Stone.h"
#include <typeinfo>
#include <iostream>
#ifndef _SERVER
#include "App.h"
#endif

BlockRegister::BlockRegister()
{
	std::cout << this << std::endl;
	//RegisterBlock(nullptr, 0);
	unsigned short i;
	blockTypeList.push_back(nullptr);
	blockList.push_back(nullptr);
	RegisterBlock(new BlockSolid(i), typeid(BlockSolid).hash_code()); i++;
	RegisterBlock(new BlockBackground(i), typeid(BlockBackground).hash_code()); i++;
	RegisterBlock(new BlockGravity(i), typeid(BlockGravity).hash_code()); i++;
	RegisterBlock(new BlockChest(i), typeid(BlockChest).hash_code()); i++;
	RegisterBlock(new Stone(i), typeid(Stone).hash_code()); i++;
}

void BlockRegister::RegisterBlock(Block *block, const size_t typeId)
{
	std::cout << blockTypeList.size() << std::endl;
	blockList.push_back(block);
	blockIdMap.emplace(typeId, blockTypeList.size());
	blockTypeList.push_back(block->RegisterBlock(blockTypeList.size()));
}

#ifndef _SERVER
void BlockRegister::RegisterBlockTextures(TextureContainer &Tc)
{
	blockTextureList.reserve(blockTypeList.size());
	blockTextureList.push_back(nullptr);
	for (int i = 1; i < blockTypeList.size(); i++)
	{
		blockTextureList.push_back(Tc.getTextures(blockList[i]->getTextureName()));
	}
}
#endif

Block *BlockRegister::getBlockType(const unsigned short id)
{
	if (id == 0)
		return nullptr;
	return (id >= blockTypeList.size()) ? nullptr : blockTypeList[id](0);
}

#ifndef _SERVER
sf::Sprite *BlockRegister::getBlockTextures(const Block *block)
{
	return blockTextureList[getBlockIdByTypeId(typeid(*block).hash_code())];
}
#endif

unsigned short BlockRegister::getBlockIdByTypeId(const size_t typeId)
{
	auto it = blockIdMap.find(typeId);//blockIdMapfind(typeId);
	//std::cout << it->second << " " << typeId << std::endl;
	return (it == blockIdMap.end()) ? 0 : it->second;
}