#pragma once

#include "Cobalt.h"
using namespace Cobalt;

#include "Editor/Panels/EditorPanel.h"
#include "Editor/Panels/Profiler/Timer.h"
#include "Editor/Panels/Profiler/ProfilerData.h"

class ProfilerPanel : public EditorPanel
{
public:
	ProfilerPanel();

	static ProfilerPanel& Get() { return *s_Instance; }

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