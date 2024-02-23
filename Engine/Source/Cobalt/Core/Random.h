#pragma once

#include <random>

namespace Cobalt
{
	class Random
	{
	public:
		static void Init();

		static float Float();
		static float Range(float min, float max);
		static int RangeInt(int min, int max);

		static uint64_t UUID();

	private:
		static std::mt19937 s_RandomEngine;
		static std::uniform_int_distribution<std::mt19937::result_type> s_Distribution;

		static std::mt19937_64 s_RandomEngine64;
		static std::uniform_int_distribution<std::mt19937_64::result_type> s_Distribution64;
	};
}