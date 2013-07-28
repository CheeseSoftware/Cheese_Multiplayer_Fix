#include "BlockRegister.h"
#include "TextureContainer.h"
#include "Block.h"

BlockRegister::BlockRegister()
{
	blockTypeList.emplace(0, nullptr);
}

void BlockRegister::RegisterBlock(TextureContainer tC, Block *block, size_t typeId)
{
	blockTypeList.emplace(typeId,block->RegisterBlock(blockTypeList.size()));
}

Block *BlockRegister::getBlockType(unsigned short id, unsigned short metadata)
{
	return (id > blockTypeList.size())? nullptr : blockTypeList[id](metadata);
}

Block *BlockRegister::getBlockTypeByTypeId(size_t typeId, unsigned short metadata)
{
	auto it = blockTypeList.find(typeId);
	return (it == blockTypeList.end()) ? nullptr : it->second(metadata);
}