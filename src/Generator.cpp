#include <iostream>
#include "Generator.h"
#include "GameUtility.h"
#include "Chunk.h"

Chunk *StandardGenerator::operator() (long x, long y, GameUtility *gameUtility)
{
	double strength;
	Chunk *chunk = new Chunk();
		for (unsigned char xx = 0; xx < 16; xx++)
	{
		for (unsigned char yy = 0; yy < 16; yy++)
		{
			strength = noiseModule.GetValue(x+xx, y+yy, 0)
				*(y+yy);

			//if (strength > 0.5)
			//	chunk->setBlock(2, xx, yy, gameUtility->blockRegister

			std::cout << strength << std::endl;
		}
	}
	return chunk;
}