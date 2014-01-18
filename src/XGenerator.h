#pragma once
#include "SeedGenerator.h"

namespace generator
{
	class XGenerator : public SeedGenerator
	{
	public:
		XGenerator();
		XGenerator(const int seed);
		virtual Chunk *operator() (long x, long y, GameUtility *gameUtility);
	};
}