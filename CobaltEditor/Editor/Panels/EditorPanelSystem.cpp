#include "Editor/Panels/EditorPanelSystem.h"
#include "Editor/Panels/EditorPanel.h"

#include "Editor/Panels/Profiler/ProfilerPanel.h"

EditorPanelSystem* EditorPanelSystem::s_Instance = nullptr;

void EditorPanelSystem::Init()
{
	s_Instance = new EditorPanelSystem();
}

void EditorPanelSystem::Update()
{
	PROFILER_START_HEADER("Panels");

	for (auto* panel : s_Instance->m_Panels)
	{
		PROFILER_TIMER_SCOPE(panel->GetName());
		panel->Update();
	}

	PROFILER_STOP_HEADER;
}

void EditorPanelSystem::PushPanel(EditorPanel* panel)
{
	s_Instance->m_Panels.push_back(panel);
}
