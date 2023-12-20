#include "cbpch.h"

#include "Cobalt/Particles/ParticleData.h"

namespace Cobalt
{
	namespace Utils
	{
		template<typename T, typename U>
		inline void Fill(T* array, size count, U value)
		{
			std::fill(array, array + count, value);
		}

		template<typename T>
		inline void Swap(T& attrib, size a, size b)
		{
			auto temp = std::move(attrib[a]);
			attrib[a] = std::move(attrib[b]);
			attrib[b] = std::move(temp);
		}
	}

	void ParticleData::Generate(size maxCount)
	{
		m_MaxCount = maxCount;
		m_Count = 0;

		Position.reset(new Vec3[m_MaxCount]);
		Velocity.reset(new Vec3[m_MaxCount]);
		Acceleration.reset(new Vec3[m_MaxCount]);
		CurrentColor.reset(new Color[m_MaxCount]);
		StartColor.reset(new Color[m_MaxCount]);
		EndColor.reset(new Color[m_MaxCount]);
		LifeTime.reset(new float[m_MaxCount]);
		IsAlive.reset(new bool[m_MaxCount]);

		Utils::Fill(Position.get(), m_MaxCount, Vec3(0.0f));
		Utils::Fill(Velocity.get(), m_MaxCount, Vec3(0.0f));
		Utils::Fill(Acceleration.get(), m_MaxCount, Vec3(0.0f));
	}

	void ParticleData::Wake(size index)
	{
		if (m_Count >= m_MaxCount) return;

		IsAlive[index] = true;
		SwapData(index, m_Count++);
	}

	void ParticleData::Kill(size index)
	{
		if (m_Count <= 0) return;

		IsAlive[index] = false;
		ResetData(index);
		SwapData(index, --m_Count);
	}

	void ParticleData::SwapData(size a, size b)
	{
		Utils::Swap(Position, a, b);
		Utils::Swap(Velocity, a, b);
		Utils::Swap(Acceleration, a, b);
		Utils::Swap(CurrentColor, a, b);
		Utils::Swap(StartColor, a, b);
		Utils::Swap(EndColor, a, b);
		Utils::Swap(LifeTime, a, b);
		Utils::Swap(IsAlive, a, b);
	}

	void ParticleData::ResetData(size index)
	{
		// TODO: Get values from a struct or something
		Position[index] = Vec3(0.0f);
		Velocity[index] = Vec3(0.0f);
		Acceleration[index] = Vec3(0.0f);
		CurrentColor[index] = Color(255);
		StartColor[index] = Color(255);
		EndColor[index] = Color(255);
		LifeTime[index] = 0.0f;
	}
}