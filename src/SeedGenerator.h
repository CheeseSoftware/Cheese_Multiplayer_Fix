#pragma once
#include <noise\noise.h>

#include "IGenerator.h"
namespace generator
{
	class SeedGenerator : public IGenerator
	{
	protected:
		noise::module::Perlin noiseModule;

		SeedGenerator();
		SeedGenerator(const int seed);
	public:
		const int getSeed() const;
	};
}