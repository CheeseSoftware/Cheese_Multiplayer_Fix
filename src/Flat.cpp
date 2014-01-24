#include "Flat.h"

#include <iostream>
#include <time.h>

#include "GameUtility.h"
#include "Chunk.h"
#include "BlockRegister.h"
#include "BlockSolid.h"

namespace generator
{
	Chunk *Flat::operator() (long x, long y, GameUtility *gameUtility)
	{
		Chunk *chunk = new Chunk();
		if (y >= 0)
		{
			for (int xx = 0; xx < 16; xx++)
			{
				for (int yy = 0; yy < 16; yy++)
				{
					chunk->setBlock(2, xx, yy,
						gameUtility->getBlockRegister().getBlockType(
							gameUtility->getBlockRegister().getBlockIdByTypeId(
								typeid(BlockSolid).hash_code())));

					chunk->setMetadata(2, xx, yy, 8);
				}
			}
		}
		return chunk;
	}
}