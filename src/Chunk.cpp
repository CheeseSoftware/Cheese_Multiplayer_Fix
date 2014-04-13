#include "Chunk.h"

#include <typeinfo>
#ifdef CLIENT
#include <SFML\Graphics.hpp>
#endif

#include "Block.h"
#include "BlockGravity.h"
#include "TextureContainer.h"
#include "camera.h"
#include "App.h"
#include "GameUtility.h"
#include "BlockRegister.h"
#include "Game.h"

Chunk::Chunk()
{ 
	for(int l = 0; l < 6; l++)
	{
		for (int x = 0; x < CHUNKWIDTH; x++)
		{
			for (int y = 0; y < CHUNKHEIGHT; y++)
			{
				blockList[x][y][l].first = nullptr;
				//blockList[x][y][l].first = new BlockGravity(3);
			}
		}
	}
}			

Chunk::~Chunk(void)
{
	for(int l = 0; l < 6; l++)
	{
		for (int i = 0; i < CHUNKWIDTH; i++)
		{
			for (int j = 0; j < CHUNKHEIGHT; j++)
			{
				delete this->blockList[i][j][l].first;
			}
		}
	}
}

bool Chunk::isAnySolid(std::pair<Block*, unsigned short> blocks[6])
{
	for(int l = 0; l < 6; l++)
	{
		if(blocks[l].first != nullptr && blocks[l].first->isSolid())
			return true;
	}
	return false;
}

bool Chunk::isAnySeeThrough(std::pair<Block*, unsigned short> blocks[6])
{
	for(int l = 0; l < 6; l++)
	{
		if(blocks[l].first != nullptr && blocks[l].first->isSeeThrough())
			return true;
	}
	return false;
}

Block *Chunk::getHighestBlock(unsigned char x, unsigned char y)
{
	for(int l = 5; l >= 0; l--)
	{
		if(blockList[x][y][l].first != nullptr)
			return blockList[x][y][l].first;
	}
	return(0);
}

#ifdef CLIENT
void Chunk::Draw(long xPos, long yPos, App &app, Game *game, GameUtility *gameUtility)
{
	Block *air = gameUtility->getBlockRegister().getBlockType(2);
	int startX = (app.getView().getCenter().x - (app.getSize().x/2))/16 - (xPos*CHUNKWIDTH);
	int startY = (app.getView().getCenter().y - (app.getSize().y/2))/16 - (yPos*CHUNKHEIGHT);
	int endX = (app.getView().getCenter().x + (app.getSize().x/2))/16+32 - (xPos*CHUNKWIDTH);
	int endY = (app.getView().getCenter().y + (app.getSize().y/2))/16+32 - (yPos*CHUNKHEIGHT);


	startX = (startX<0)? 0 : startX;
	startY = (startY<0)? 0 : startY;
	endX = (endX > CHUNKWIDTH)? CHUNKWIDTH : endX;
	endY = (endY > CHUNKHEIGHT)? CHUNKHEIGHT : endY;

	for(long x = startX; x < endX; x++)
	{
		for(long y = startY; y < endY; y++)
		{
			long xPosBlock = (16*xPos-16 + x)*16;
			long yPosBlock = (16*yPos-16 + y)*16;
			for(int l = 5; l >= 0; l--)
			{
				if(blockList[x][y][l].first != nullptr )
				{
					blockList[x][y][l].first->Draw((xPos - 1 << 4) + x << 4, (yPos - 1 << 4) + y << 4, app, game, gameUtility, blockList[x][y][l].second); 
					if(!blockList[x][y][l].first->isSeeThrough())
						break;
				}
			}
			/*bool noob = true;
			for(int i = 5; i >= 0; i--)
			{
				if(blockList[x][y][i].first != nullptr)
					noob = false;
			}
			if(noob)
				air->Draw((xPos - 1 << 4) + x << 4, (yPos - 1 << 4) + y << 4, app, gameUtility, 12);*/
		}
	}
}
#endif

void Chunk::setBlock(unsigned char layer, unsigned short x, unsigned short y, Block *block)
{
	if (x >= 16 || y >= 16)
		return;
	if (blockList[x][y][layer].first != nullptr)
		blockList[x][y][layer].first->OnRemove();

	blockList[x][y][layer].first = block;
}

void Chunk::setMetadata(unsigned char layer, unsigned short x, unsigned short y, unsigned short metadata)
{
	blockList[x][y][layer].second = metadata;
}

Block *Chunk::getBlock(unsigned char layer, unsigned short x, unsigned short y)
{
	return blockList[x][y][layer].first;
}

std::pair<Block*, unsigned short> &Chunk::getBlockAndMetadata(unsigned short x, unsigned short y, unsigned short layer)
{
	return blockList[x][y][layer];
}

short Chunk::getMetadata(unsigned char layer, unsigned short x, unsigned short y) { return blockList[x][y][layer].second; }

unsigned short Chunk::getBlockId(unsigned char layer, unsigned short x, unsigned short y, GameUtility* gameUtility)
{
	return gameUtility->getBlockRegister().getBlockIdByTypeId(
		typeid(*blockList[x][y][layer].first).hash_code());
}