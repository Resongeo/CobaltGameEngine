#pragma once

#include "Cobalt/Core/Core.h"
#include "Cobalt/Core/Types/Math.h"
#include "Cobalt/Particles/ParticleData.h"

namespace Cobalt
{
	enum class ParticleGeneratorType
	{
		None = 0,
		BoxPosition,
		Lifetime,
		Velocity
	};

	class ParticleGenerator
	{
	public:
		ParticleGenerator(ParticleGeneratorType type) : Type(type) {}

		virtual void Generate(ParticleData& particleData, size startIndex, size endIndex) = 0;

		Vec3 PositionOffset = Vec3(0.0f);
		ParticleGeneratorType Type = ParticleGeneratorType::None;

		template<typename T>
		static inline Shared<T> Create()
		{
			return CreateRef<T>();
		}
	};
}