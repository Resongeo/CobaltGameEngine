#pragma once

#include "Cobalt.h"
using namespace Cobalt;

#include "Editor/Panels/EditorPanel.h"

class Timer
{
public:
	Timer(const char* name);
	~Timer();

private:
	const char* m_Name;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTime;
};


struct ProfilerResult
{
	const char* Name;
	float Duration;

	ProfilerResult(const char* name, float duration) : Name(name), Duration(duration) {}
};

struct ProfilerHeader
{
	const char* Name;
	std::vector<ProfilerResult> Results;

	ProfilerHeader() = default;
	ProfilerHeader(const char* name) : Name(name) {}
};

class ProfilerPanel : public EditorPanel
{
public:
	ProfilerPanel();

	inline static ProfilerPanel& Get() { return *s_Instance; }

	virtual void Update() override;

	void StartProfilerHeader(const char* name);
	void StopProfilerHeader();
	void AddProfilerResult(const char* name, float duration);

private:
	static ProfilerPanel* s_Instance;

	ProfilerHeader m_ActiveHeader;
	std::vector<ProfilerHeader> m_ProfilerHeaders;
};

#define PROFILER_START_HEADER(...)	ProfilerPanel::Get().StartProfilerHeader(__VA_ARGS__)
#define PROFILER_STOP_HEADER		ProfilerPanel::Get().StopProfilerHeader()

#define PROFILER_TIMER_SCOPE(...)	Timer timer(__VA_ARGS__)