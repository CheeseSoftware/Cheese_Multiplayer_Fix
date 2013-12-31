#include <iostream>
#include "WeirdGenerator.h"
#include "GameUtility.h"
#include "Chunk.h"
#include <time.h>

#include "BlockSolid.h"

namespace generator
{
	WeirdGenerator::WeirdGenerator()
		: StandardGenerator()
	{
	}

	WeirdGenerator::WeirdGenerator(int seed)
		: StandardGenerator(seed)
	{
	}

	Chunk *WeirdGenerator::operator() (long x, long y, GameUtility *gameUtility)
	{
		if (x == 0)
		{
			Chunk *chunk = new Chunk();
			if (y < 0)
			{
				for (char xx = 0; xx < 16; xx++)
				{
					for(char yy = 0; yy < 16; yy++)
					{
						chunk->setBlock(2, xx, yy, gameUtility->getBlockRegister().getBlockType(3));
						chunk->setMetadata(2, xx, yy, 1);
					}
				}
			}
			return chunk;
		}
		else
			return StandardGenerator::operator()(x, y, gameUtility);
	}
}