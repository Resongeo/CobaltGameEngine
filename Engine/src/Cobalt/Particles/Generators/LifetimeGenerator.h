#pragma once

#include "Cobalt/Particles/Generators/ParticleGenerator.h"

namespace Cobalt
{
	class LifetimeGenerator : public ParticleGenerator
	{
	public:
		LifetimeGenerator() : ParticleGenerator(ParticleGeneratorType::Lifetime) {}

		void Generate(ParticleData& particleData, size_t startIndex, size_t endIndex) override;

		float Min = 1.0f;
		float Max = 1.0f;
	};
}