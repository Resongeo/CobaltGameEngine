#pragma once

#include "Cobalt/Core/Types.h"

namespace Cobalt
{
	struct ParticleSystemSpecification
	{
		u32 MaxParticles = 1000;
		bool StartsWithScene = true;

		ParticleSystemSpecification() = default;
		ParticleSystemSpecification(const ParticleSystemSpecification&) = default;
	};
}