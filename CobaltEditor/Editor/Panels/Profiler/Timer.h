#pragma once

#include "Cobalt.h"
using namespace Cobalt;

class Timer
{
public:
	Timer(const char* name);
	~Timer();

private:
	const char* m_Name;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTime;
};