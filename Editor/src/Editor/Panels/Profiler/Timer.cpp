#include "Editor/Panels/Profiler/Timer.h"
#include "Editor/Panels/Profiler/ProfilerPanel.h"

Timer::Timer(const char* name) : m_Name(name)
{
	m_StartTime = std::chrono::high_resolution_clock::now();
}

Timer::~Timer()
{
	auto endTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - m_StartTime).count() * 0.001f;

	ProfilerPanel::Get().AddProfilerResult(m_Name, duration);
}