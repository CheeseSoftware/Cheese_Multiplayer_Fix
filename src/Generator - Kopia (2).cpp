/*#include <iostream>
#include "Generator.h"
#include "GameUtility.h"
#include "Chunk.h"
#include <time.h>

#include "BlockSolid.h"

const int SeedGenerator::getSeed() const
{
	return noiseModule.GetSeed();
}

SeedGenerator::SeedGenerator()
{
	noiseModule.SetSeed(time(nullptr));
}

SeedGenerator::SeedGenerator(const int seed)
{
	noiseModule.SetSeed(seed);
}

StandardGenerator::StandardGenerator()
	: SeedGenerator()
{
}

StandardGenerator::StandardGenerator(int seed)
	: SeedGenerator(seed)
{
}

Chunk *StandardGenerator::operator() (long x, long y, GameUtility *gameUtility)
{
	double strength;
	Chunk *chunk = new Chunk();

	for (unsigned char xx = 0; xx < 16; xx++)
	{
		for (unsigned char yy = 0; yy < 16; yy++)
		{
			strength = /*noiseModule.GetValue((double)x+(double)xx/16.0, (double)y+(double)yy/16.0, 0)/2* /
				+(y*16+yy) / ((y < 0)? 1024: 1024.0)
				+ noiseModule.GetValue(((double)x+(double)xx/16.0)/64,((double)y+(double)yy/16.0)/64, 10)/4+0.5;//*(y*16+yy)/1024.0;

			if (strength > 0.5)
			{
				//strength -= noiseModule.GetValue((double)x/4.0+(double)xx/64.0, (double)y/4.0+(double)yy/64.0, 0)/32;
				double caveStrength = noiseModule.GetValue(((double)x+(double)xx/16.0)/4, ((double)y+(double)yy/16.0)/4, 0);
				if (caveStrength > 0.0
					&& caveStrength + noiseModule.GetValue(((double)x+(double)xx/16.0)/128, ((double)y+(double)yy/16)/128, 10) > -0.50)
				{
					if (strength > 0.5 + 1.0 / 128.0)
					{
						chunk->setBlock(2, xx, yy, gameUtility->getBlockRegister().getBlockType(5));
						chunk->setMetadata(2, xx, yy, 0);
					}
					else
					{
						chunk->setBlock(2, xx, yy, gameUtility->getBlockRegister().getBlockType(6));
						chunk->setMetadata(2, xx, yy, 0);
						//chunk->setBlock(2, xx, yy, gameUtility->getBlockRegister().getBlockType(1));
						//chunk->setMetadata(2, xx, yy, 1);
					}
				}
			}

			//std::cout << "strength:\t" << strength << std::endl;
		}
	}
	return chunk;
}

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


XGenerator::XGenerator()
	: SeedGenerator()
{
}

XGenerator::XGenerator(const int seed)
	: SeedGenerator(seed)
{
}


Chunk *XGenerator::operator() (long x, long y, GameUtility *gameUtility)
{
	return nullptr;
}



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


Chunk *Flat::operator() (long x, long y, GameUtility *gameUtility)
{
	Chunk *chunk = new Chunk();
	if (x <= 0)
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

Chunk *Pyramid::operator() (long x, long y, GameUtility *gameUtility)
{
	Chunk *chunk = new Chunk();
	if (x <= 0)
	{
		for (int xx = 0; xx < 16; xx++)
		{
			for (int yy = 0; yy < 16; yy++)
			{
				if (y*16 + yy > floor((double)abs(x*16+xx)/2.0-((x < 1 || (x < 0 && xx < 15))? 0.25:0.0) ) *2.0)
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
}*/