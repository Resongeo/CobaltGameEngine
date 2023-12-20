#include "cbpch.h"

#include "Cobalt/Core/Time.h"
#include "Cobalt/Particles/ParticleEmitter.h"

namespace Cobalt
{
	void ParticleEmitter::Emit(ParticleData& particleData)
	{
        size startIndex = particleData.GetCount();
        size endIndex = startIndex + EmitRate;

        if (endIndex >= particleData.GetMaxCount()) endIndex = particleData.GetMaxCount();

        for (auto& generator : m_Generators)
            generator->Generate(particleData, startIndex, endIndex);

        for (size i = startIndex; i < endIndex; i++)
            particleData.Wake(i);
	}
}