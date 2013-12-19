#pragma once
#include "IGenerator.h"

class Flat : public IGenerator
{
public:
	virtual Chunk *operator() (long x, long y, GameUtility *gameUtility);
};