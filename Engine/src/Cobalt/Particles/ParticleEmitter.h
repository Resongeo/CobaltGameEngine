#pragma once

#include "Cobalt/Core/Core.h"
#include "Cobalt/Particles/ParticleData.h"
#include "Cobalt/Particles/Generators/ParticleGenerator.h"

namespace Cobalt
{
	class ParticleEmitter
	{
	public:
		ParticleEmitter() = default;

		void Emit(ParticleData& particleData);
		void AddGenerator(const Ref<ParticleGenerator>& generator) { m_Generators.push_back(generator); }

	public:
		size_t EmitRate = 1;

	private:
		std::vector<Ref<ParticleGenerator>> m_Generators;

		friend class ParticleSystem;
	};
}