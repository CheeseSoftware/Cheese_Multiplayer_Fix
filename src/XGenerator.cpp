#include <iostream>
#include "XGenerator.h"
#include "GameUtility.h"
#include "Chunk.h"
#include <time.h>

#include "BlockSolid.h"

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
