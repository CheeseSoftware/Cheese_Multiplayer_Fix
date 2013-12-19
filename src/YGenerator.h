#pragma once
#include "IGenerator.h"

class YGenerator : public IGenerator
{
public:
	YGenerator();
	virtual Chunk *operator() (long x, long y, GameUtility *gameUtility);
};
