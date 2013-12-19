#include <iostream>
#include "YGenerator.h"
#include "GameUtility.h"
#include "Chunk.h"
#include <time.h>

#include "BlockSolid.h"

YGenerator::YGenerator()
{

}

Chunk *YGenerator::operator() (long x, long y, GameUtility *gameUtility)
{
	Chunk *chunk = new Chunk();

	if (y == 0)
	{
		for (int xx = 0; xx < 16; xx ++)
		{
			chunk->setBlock(2, xx, 0,
				gameUtility->getBlockRegister().getBlockType(
					gameUtility->getBlockRegister().getBlockIdByTypeId(
						typeid(BlockSolid).hash_code())));

			chunk->setMetadata(2, xx, 0, 8);
		}
	}

	return chunk;
}