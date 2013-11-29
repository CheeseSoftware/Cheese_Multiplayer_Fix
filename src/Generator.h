#pragma once
#include <noise\noise.h>

class GameUtility;
class Chunk;

//class Chunk;

class AGenerator
{
protected:
	/*RANDOM-generator och sånt*/
public:
	virtual Chunk *operator() (long x, long y, GameUtility *gameUtility)=0;
};

class StandardGenerator : public AGenerator
{
protected:
	noise::module::Perlin noiseModule;
public:
	StandardGenerator();
	StandardGenerator(const int seed);
	virtual Chunk *operator() (long x, long y, GameUtility *gameUtility);
	const int getSeed() const;
};

class WeirdGenerator : public StandardGenerator
{
public:
	WeirdGenerator();
	WeirdGenerator(const int seed);
	virtual Chunk *operator() (long x, long y, GameUtility *gameUtility);
};