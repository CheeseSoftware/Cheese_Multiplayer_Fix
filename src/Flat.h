#pragma once
#include "IGenerator.h"

namespace generator
{
	class Flat : public IGenerator
	{
	public:
		virtual Chunk *operator() (long x, long y, GameUtility *gameUtility);
	};
}