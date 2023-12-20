#pragma once

#include "Cobalt/Particles/Generators/ParticleGenerator.h"

namespace Cobalt
{
	class BoxPositionGenerator : public ParticleGenerator
	{
	public:
		BoxPositionGenerator() : ParticleGenerator(ParticleGeneratorType::BoxPosition) {}

		void Generate(ParticleData& particleData, size startIndex, size endIndex) override;

		Vec3 MinPosition = Vec3(-1.0f);
		Vec3 MaxPosition = Vec3(1.0f);
	};
}