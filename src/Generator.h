#pragma once
#include <noise\noise.h>

class GameUtility;
class Chunk;

//class Chunk;

class AGenerator
{
protected:
	noise::module::Perlin noiseModule;
	/*RANDOM-generator och sånt*/
public:
	virtual Chunk *operator() (long x, long y, GameUtility *gameUtility)=0;
};

class StandardGenerator : public AGenerator
{
public:
	virtual Chunk *operator() (long x, long y, GameUtility *gameUtility);
};