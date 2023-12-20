#include "cbpch.h"
#include "Cobalt/Particles/Generators/BoxPositionGenerator.h"
#include "Cobalt/Core/Random.h"

#include <glm/gtc/random.hpp>

namespace Cobalt
{
	void Cobalt::BoxPositionGenerator::Generate(ParticleData& particleData, size startIndex, size endIndex)
	{
		Vec3 minPos = PositionOffset - MinPosition;
		Vec3 maxPos = PositionOffset + MaxPosition;

		for (size i = startIndex; i < endIndex; i++)
		{
			particleData.Position[i] = Vec3(Random::Range(MinPosition.x, MaxPosition.x), Random::Range(MinPosition.y, MaxPosition.y), 0.0f);
		}
	}
}