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
		for (Ref<EditorPanel> panel : s_Instance->m_Panels)
			panel->OnUpdate();
	}

	void EditorPanelManager::UIRender()
	{
		for (Ref<EditorPanel> panel : s_Instance->m_Panels)
			panel->OnUIRender();
	}

	void EditorPanelManager::OnEvent(Event& event)
	{
		for (Ref<EditorPanel> panel : s_Instance->m_Panels)
			panel->OnEvent(event);
	}

	void EditorPanelManager::PushPanel(Ref<EditorPanel>&& panel)
	{
		s_Instance->m_Panels.push_back(std::move(panel));
	}
}