#include "BlockRegister.h"
#include "ITextureContainer.h"
#include "Block.h"
#include "BlockSolid.h"
#include "BlockBackground.h"
#include "BlockGravity.h"
#include "BlockChest.h"
#include "Stone.h"
#include "Dirt.h"
#include <typeinfo>
#include <iostream>
#ifdef CLIENT
#include "App.h"
#endif

BlockRegister::BlockRegister()
{
	std::cout << this << std::endl;
	//RegisterBlock(nullptr, 0);
	unsigned short i = 0;
	blockTypeList.push_back(nullptr);
	blockList.push_back(nullptr);
	RegisterBlock(new BlockSolid(), typeid(BlockSolid).hash_code()); i++;
	RegisterBlock(new BlockBackground(), typeid(BlockBackground).hash_code()); i++;
	RegisterBlock(new BlockGravity(), typeid(BlockGravity).hash_code()); i++;
	RegisterBlock(new BlockChest(), typeid(BlockChest).hash_code()); i++;
	RegisterBlock(new Stone(), typeid(Stone).hash_code()); i++;
	RegisterBlock(new Dirt(), typeid(Dirt).hash_code()); i++;
}

void BlockRegister::RegisterBlock(Block *block, const size_t typeId)
{
	std::cout << blockTypeList.size() << std::endl;
	blockList.push_back(block);
	blockIdMap.emplace(typeId, blockTypeList.size());
	blockTypeList.push_back(block->RegisterBlock(blockTypeList.size()));
}

#ifdef CLIENT
void BlockRegister::RegisterBlockTextures(ITextureContainer *Tc)
{
	blockTextureList.reserve(blockTypeList.size());
	blockTextureList.push_back(nullptr);
	for (int i = 1; i < blockTypeList.size(); i++)
	{
		blockTextureList.push_back(Tc->getTextures(blockList[i]->getTextureName()));
	}
}
#endif

Block *BlockRegister::getBlockType(const unsigned short id)
{
	if (id == 0)
		return nullptr;
	if(id == 4)
	{
		Block *block = new BlockChest();
		return block;
	}
	return (id >= blockTypeList.size()) ? nullptr : blockTypeList[id](0);
}

#ifdef CLIENT
sf::Sprite **BlockRegister::getBlockTextures(const Block *block)
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