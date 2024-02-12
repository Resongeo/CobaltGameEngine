#pragma once

#include "Cobalt/Core/Types.h"
#include "Cobalt/Particles/ParticleData.h"
#include "Cobalt/Particles/Generators/ParticleGenerator.h"

namespace Cobalt
{
	class ParticleEmitter
	{
	public:
		ParticleEmitter() = default;

		void Emit(ParticleData& particleData);
		void AddGenerator(const Shared<ParticleGenerator>& generator) { m_Generators.push_back(generator); }

	public:
		size EmitRate = 1;

	private:
		Vector<Shared<ParticleGenerator>> m_Generators;

		friend class ParticleSystem;
	};
}