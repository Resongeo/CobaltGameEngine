#include "cbpch.h"

#include "Cobalt/Core/Random.h"
#include "Cobalt/Particles/Generators/LifetimeGenerator.h"

namespace Cobalt
{
	void LifetimeGenerator::Generate(ParticleData& particleData, size_t startIndex, size_t endIndex)
	{
		for (size_t i = startIndex; i < endIndex; i++)
		{
			particleData.LifeTime[i] = Random::Range(Min, Max);
		}
	}
}

