#include "cbpch.h"

#include "Cobalt/Core/Random.h"

namespace Cobalt
{
	std::mt19937 Random::s_RandomEngine;
	std::uniform_int_distribution<std::mt19937::result_type> Random::s_Distribution;

	std::mt19937_64 Random::s_RandomEngine64;
	std::uniform_int_distribution<std::mt19937_64::result_type> Random::s_Distribution64;

	void Random::Init()
	{
		s_RandomEngine.seed(std::random_device()());
	}
	
	float Random::Float()
	{
		return (float)s_Distribution(s_RandomEngine) / (float)std::numeric_limits<uint32_t>::max();
	}
	
	float Random::Range(float min, float max)
	{
		return Random::Float() * (max - min) + min;
	}

	int Random::RangeInt(int min, int max)
	{
		return (int)Random::Range((float)min, (float)max + 1);
	}

	uint64_t Random::ID()
	{
		return s_Distribution64(s_RandomEngine64);
	}
}