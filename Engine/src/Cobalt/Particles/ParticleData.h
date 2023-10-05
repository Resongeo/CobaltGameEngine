#pragma once

#include "Cobalt/Core/Core.h"
#include "Cobalt/Core/Math.h"
#include "Cobalt/Core/Color.h"

namespace Cobalt
{
	class ParticleData
	{
	public:
		ParticleData() = default;

		void Generate(size_t maxCount);
		void Wake(size_t index);
		void Kill(size_t index);

		inline size_t GetCount() const { return m_Count; }
		inline size_t GetMaxCount() const { return m_MaxCount; }

	public:
		Scope<Vec3[]> Position;
		Scope<Vec3[]> Velocity;
		Scope<Vec3[]> Acceleration;
		Scope<Color[]> CurrentColor;
		Scope<Color[]> StartColor;
		Scope<Color[]> EndColor;
		Scope<float[]> LifeTime;
		Scope<bool[]> IsAlive;

	private:
		void SwapData(size_t a, size_t b);
		void ResetData(size_t index);

	private:
		size_t m_MaxCount = 0;
		size_t m_Count = 0;
	};
}