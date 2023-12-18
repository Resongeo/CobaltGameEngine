#pragma once

#include "Cobalt/Particles/Generators/ParticleGenerator.h"

namespace Cobalt
{
	class VelocityGenerator : public ParticleGenerator
	{
	public:
		VelocityGenerator() : ParticleGenerator(ParticleGeneratorType::Velocity) {}

		void Generate(ParticleData& particleData, size_t startIndex, size_t endIndex) override;

		Vec3 MinDirection = Vec3(-1.0f);
		Vec3 MaxDirection = Vec3(1.0f);
	};
}