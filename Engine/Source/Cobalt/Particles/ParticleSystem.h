#pragma once

#include "Cobalt/Core/Core.h"
#include "Cobalt/Particles/ParticleData.h"
#include "Cobalt/Particles/ParticleEmitter.h"
#include "Cobalt/Particles/ParticleSystemState.h"
#include "Cobalt/Particles/ParticleSystemSpecification.h"

namespace Cobalt
{
	class ParticleSystem
	{
	public:
		ParticleSystem() = default;

		void Start();
		void Pause();
		void Resume();
		void Reset();
		void Update();

		void AddGenerator(const Ref<ParticleGenerator>& generator) { m_ParticleEmitter.AddGenerator(generator); }

		Vector<Ref<ParticleGenerator>> GetGenerators() const { return m_ParticleEmitter.m_Generators; }

		inline ParticleSystemState GetState() const { return m_State; }
		inline size* GetEmitRatePtr() { return &m_ParticleEmitter.EmitRate; }
		inline const ParticleSystemSpecification& GetSpecs() const { return m_Specs; }

	public:

	private:
		void BaseUpdater();
		void Render();

	private:
		ParticleData m_ParticleData;
		ParticleEmitter m_ParticleEmitter;
		ParticleSystemState m_State = ParticleSystemState::None;
		ParticleSystemSpecification m_Specs;

		friend class Scene;
	};
}