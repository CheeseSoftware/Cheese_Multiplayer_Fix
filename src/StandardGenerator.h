#pragma once
#include "SeedGenerator.h"

class StandardGenerator : public SeedGenerator
{
public:
	StandardGenerator();
	StandardGenerator(const int seed);
	virtual Chunk *operator() (long x, long y, GameUtility *gameUtility);
};