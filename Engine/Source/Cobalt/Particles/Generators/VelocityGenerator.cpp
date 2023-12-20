#include "cbpch.h"

#include "Cobalt/Core/Random.h"
#include "Cobalt/Particles/Generators/VelocityGenerator.h"

namespace Cobalt
{
	void VelocityGenerator::Generate(ParticleData& particleData, size startIndex, size endIndex)
	{
		for (size i = startIndex; i < endIndex; i++)
		{
			particleData.Velocity[i] = Vec3(Random::Range(MinDirection.x, MaxDirection.x), Random::Range(MinDirection.y, MaxDirection.y), 0.0f);
		}
	}
}