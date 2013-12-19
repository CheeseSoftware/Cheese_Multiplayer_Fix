#include <iostream>
#include "Pyramid.h"
#include "GameUtility.h"
#include "Chunk.h"
#include <time.h>

#include "BlockSolid.h"

Chunk *Pyramid::operator() (long x, long y, GameUtility *gameUtility)
{
	Chunk *chunk = new Chunk();
	if (x <= 0)
	{
		for (int xx = 0; xx < 16; xx++)
		{
			for (int yy = 0; yy < 16; yy++)
			{
				if (y*16 + yy > (((x < 0)? -1:1) * (x*16+xx)))// + (x >= 0)? 1:0)/2*2)//floor((double)abs(x*16+xx)/2.0-((x < 1 || (x < 0 && xx < 15))? 0.25:0.0) ) *2.0)
				{
					chunk->setBlock(2, xx, yy,
						gameUtility->getBlockRegister().getBlockType(
							gameUtility->getBlockRegister().getBlockIdByTypeId(
								typeid(BlockSolid).hash_code())));

					chunk->setMetadata(2, xx, yy, 17);
				}
			}
		}
	}
	return chunk;
}