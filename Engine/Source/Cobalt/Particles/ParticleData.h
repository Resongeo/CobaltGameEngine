#pragma once

#include "Cobalt/Core/Core.h"
#include "Cobalt/Core/Types/Math.h"
#include "Cobalt/Core/Types/Color.h"

namespace Cobalt
{
	class ParticleData
	{
	public:
		ParticleData() = default;

		void Generate(size maxCount);
		void Wake(size index);
		void Kill(size index);

		inline size GetCount() const { return m_Count; }
		inline size GetMaxCount() const { return m_MaxCount; }

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
		void SwapData(size a, size b);
		void ResetData(size index);

	private:
		size m_MaxCount = 0;
		size m_Count = 0;
	};
}