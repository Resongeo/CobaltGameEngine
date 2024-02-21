#include "pch.h"
#include "CobaltEditor/Core/EditorLayer.h"
#include "CobaltEditor/Components/DockSpace.h"
#include "CobaltEditor/Managers/EditorPanelManager.h"
#include "CobaltEditor/Managers/StyleManager.h"
#include "CobaltEditor/Panels/ComponentsPanel.h"
#include "CobaltEditor/Panels/MainViewportPanel.h"
#include "CobaltEditor/Panels/SceneHierarchyPanel.h"
#include "CobaltEditor/Panels/LogPanel.h"

#include "CobaltEditor/Logger/Log.h"

namespace CobaltEditor
{
	void EditorLayer::OnAttach()
	{
		m_Window = Application::GetWindow();

		StyleManager::LoadFonts();
		StyleManager::LoadStyle();

		// TODO: Do this when there is no default scene in the project file
		SceneManager::CreateDefaultScene();

		ComponentsPanel::Create();
		MainViewportPanel::Create();
		SceneHierarchyPanel::Create();
		LogPanel::Create();
	}

	void EditorLayer::OnDetach()
	{
	}

	void EditorLayer::OnUpdate()
	{
		EditorPanelManager::Update();
	}

	void EditorLayer::OnImGuiUpdate()
	{
		DockSpace::MasterSpace(m_Window);
		EditorPanelManager::UIRender();

		ImGui::Begin("Debug");

		if (ImGui::Button("Close application"))
		{
			Application::Close();
		}
		if (ImGui::Button("Restart application"))
		{
			Application::Restart();
		}

		if (ImGui::Button("Add Logs"))
		{
			Log::Trace("Trace message");
			Log::Info("Info message");
			Log::Warn("Warn message");
			Log::Error("Error message");
		}
		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& event)
	{
		EditorPanelManager::OnEvent(event);
	}
}