#pragma once
#include "StandardGenerator.h"

namespace generator
{
	class WeirdGenerator : public StandardGenerator
	{
	public:
		WeirdGenerator();
		WeirdGenerator(const int seed);
		virtual Chunk *operator() (long x, long y, GameUtility *gameUtility);
	};
}