#include "Editor/Panels/EditorPanelManager.h"
#include "Editor/Panels/EditorPanel.h"

#include "Editor/Panels/Profiler/ProfilerPanel.h"

EditorPanelManager* EditorPanelManager::s_Instance = nullptr;

void EditorPanelManager::Init()
{
	s_Instance = new EditorPanelManager();
}

void EditorPanelManager::Update()
{
	PROFILER_START_HEADER("Panels");

	for (auto* panel : s_Instance->m_Panels)
	{
		PROFILER_TIMER_SCOPE(panel->GetName());
		panel->Update();
	}

	PROFILER_STOP_HEADER;
}

void EditorPanelManager::PushPanel(EditorPanel* panel)
{
	s_Instance->m_Panels.push_back(panel);
}
