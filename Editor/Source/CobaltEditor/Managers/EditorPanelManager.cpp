#include "pch.h"
#include "CobaltEditor/Managers/EditorPanelManager.h"

namespace CobaltEditor
{
	EditorPanelManager* EditorPanelManager::s_Instance = nullptr;

	void EditorPanelManager::Init()
	{
		s_Instance = new EditorPanelManager();
	}

	void EditorPanelManager::Update()
	{
		for (Shared<EditorPanel> panel : s_Instance->m_Panels)
			panel->OnUpdate();
	}

	void EditorPanelManager::UIRender()
	{
		for (Shared<EditorPanel> panel : s_Instance->m_Panels)
			panel->OnUIRender();
	}

	void EditorPanelManager::OnEvent(Event& event)
	{
		for (Shared<EditorPanel> panel : s_Instance->m_Panels)
			panel->OnEvent(event);
	}

	void EditorPanelManager::PushPanel(const Shared<EditorPanel>& panel)
	{
		s_Instance->m_Panels.push_back(panel);
		panel->OnLoad();
	}
}