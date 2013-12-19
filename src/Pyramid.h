#pragma once
#include "IGenerator.h"

class Pyramid : public IGenerator
{
public:
	virtual Chunk *operator() (long x, long y, GameUtility *gameUtility);
};