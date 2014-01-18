#include <iostream>
#include "SeedGenerator.h"
#include "GameUtility.h"
#include "Chunk.h"
#include <time.h>

namespace generator
{
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
}