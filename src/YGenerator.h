#pragma once
#include "IGenerator.h"

namespace generator
{
	class YGenerator : public IGenerator
	{
	public:
		YGenerator();
		virtual Chunk *operator() (long x, long y, GameUtility *gameUtility);
	};
}