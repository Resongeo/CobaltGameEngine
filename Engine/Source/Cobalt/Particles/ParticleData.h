#pragma once

#include "Cobalt/Core/Types.h"

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
		Unique<Vec3[]> Position;
		Unique<Vec3[]> Velocity;
		Unique<Vec3[]> Acceleration;
		Unique<Color[]> CurrentColor;
		Unique<Color[]> StartColor;
		Unique<Color[]> EndColor;
		Unique<float[]> LifeTime;
		Unique<bool[]> IsAlive;

	private:
		void SwapData(size a, size b);
		void ResetData(size index);

	private:
		size m_MaxCount = 0;
		size m_Count = 0;
	};
}