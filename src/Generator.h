#pragma once
#include <noise\noise.h>

class GameUtility;
class Chunk;

//class Chunk;

class IGenerator

{
protected:
	/*RANDOM-generator och sånt*/
public:
	virtual Chunk *operator() (long x, long y, GameUtility *gameUtility)=0;
};

class SeedGenerator : public IGenerator
{
protected:
	noise::module::Perlin noiseModule;

	SeedGenerator();
	SeedGenerator(const int seed);
public:
	const int getSeed() const;
};

class StandardGenerator : public SeedGenerator
{
public:
	StandardGenerator();
	StandardGenerator(const int seed);
	virtual Chunk *operator() (long x, long y, GameUtility *gameUtility);
};

class WeirdGenerator : public StandardGenerator
{
public:
	WeirdGenerator();
	WeirdGenerator(const int seed);
	virtual Chunk *operator() (long x, long y, GameUtility *gameUtility);
};

class XGenerator : public SeedGenerator
{
public:
	XGenerator();
	XGenerator(const int seed);
	virtual Chunk *operator() (long x, long y, GameUtility *gameUtility);
};

class YGenerator : public IGenerator
{
public:
	YGenerator();
	virtual Chunk *operator() (long x, long y, GameUtility *gameUtility);
};

class Flat : public IGenerator
{
public:
	virtual Chunk *operator() (long x, long y, GameUtility *gameUtility);
};

class Pyramid : public IGenerator
{
public:
	virtual Chunk *operator() (long x, long y, GameUtility *gameUtility);
};