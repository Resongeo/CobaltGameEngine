#include "cbpch.h"

#include "Cobalt/Core/Random.h"
#include "Cobalt/Core/Time.h"
#include "Cobalt/Particles/ParticleSystem.h"
#include "Cobalt/Rendering/RenderCommand.h"

namespace Cobalt
{
	void ParticleSystem::Start()
	{
		if (m_State != ParticleSystemState::None) return;

		m_ParticleData.Generate(m_Specs.MaxParticles);

		m_State = ParticleSystemState::Updating;
	}

	void ParticleSystem::Pause()
	{
		m_State = ParticleSystemState::Stopped;
	}
	
	void ParticleSystem::Resume()
	{
		m_State = ParticleSystemState::Updating;
	}
	
	void ParticleSystem::Reset()
	{
		m_State = ParticleSystemState::None;
	}
	
	void ParticleSystem::Update()
	{
		if (m_State == ParticleSystemState::None) return;

		if (m_State == ParticleSystemState::Updating)
		{
			m_ParticleEmitter.Emit(m_ParticleData);

			// TODO: Have updaters

			BaseUpdater();
		}

		Render();
	}

	void ParticleSystem::BaseUpdater()
	{
		for (size_t i = 0; i < m_ParticleData.GetCount(); i++)
		{
			m_ParticleData.Position[i] += m_ParticleData.Velocity[i] * Time::deltaTime;

			m_ParticleData.LifeTime[i] -= Time::deltaTime;

			if (m_ParticleData.LifeTime[i] <= 0.0f)
				m_ParticleData.Kill(i);
		}
	}

	void ParticleSystem::Render()
	{
		for (size_t i = 0; i < m_ParticleData.GetCount(); i++)
		{
			RenderCommand::DrawQuad(m_ParticleData.Position[i], Vec3(0.1f), m_ParticleData.CurrentColor[i]);
		}
	}
}