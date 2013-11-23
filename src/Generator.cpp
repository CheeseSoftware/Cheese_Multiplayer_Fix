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
			strength = /*noiseModule.GetValue((double)x+(double)xx/16.0, (double)y+(double)yy/16.0, 0)/2*/
				+(y*16+yy) / ((y < 0)? 1024.0: 1024.0)
				+ noiseModule.GetValue((double)x/64+(double)xx/1024.0, 0, 10)/4+0.5;//*(y*16+yy)/1024.0;

			if (strength > 0.5)
			{
				//strength -= noiseModule.GetValue((double)x/4.0+(double)xx/64.0, (double)y/4.0+(double)yy/64.0, 0)/32;

				if (noiseModule.GetValue((double)x+(double)xx/16.0, (double)y+(double)yy/16.0, 0) > -0.5)
				{
					if (strength > 0.53125)
					{
						chunk->setBlock(2, xx, yy, gameUtility->getBlockRegister().getBlockType(1));
						chunk->setMetadata(2, xx, yy, 14);
					}
					else
					{
						chunk->setBlock(2, xx, yy, gameUtility->getBlockRegister().getBlockType(1));
						chunk->setMetadata(2, xx, yy, 1);
					}
				}
			}

			//std::cout << "strength:\t" << strength << std::endl;
		}
	}
	return chunk;
}