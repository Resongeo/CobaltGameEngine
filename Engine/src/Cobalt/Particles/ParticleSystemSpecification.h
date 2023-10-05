#pragma once

namespace Cobalt
{
	struct ParticleSystemSpecification
	{
		uint32_t MaxParticles = 1000;
		bool StartsWithScene = true;

		ParticleSystemSpecification() = default;
		ParticleSystemSpecification(const ParticleSystemSpecification&) = default;
	};
}