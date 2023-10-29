#include "CobaltEditor/Core/EditorLayer.h"
#include "CobaltEditor/Components/DockSpace.h"
#include "CobaltEditor/Managers/EditorPanelManager.h"

#include "CobaltEditor/Panels/MainViewportPanel.h"
#include "CobaltEditor/Panels/SceneHierarchyPanel.h"

namespace CobaltEditor
{
	void EditorLayer::OnAttach()
	{
		ImGuiIO& io = ImGui::GetIO();
		io.IniFilename = "..\\imgui.ini";

		m_Window = Application::GetWindow();
		m_Scene = CreateRef<Scene>("Scene");
		auto entity = m_Scene->CreateEntity("Red Square");
		entity.AddComponent<SpriteRendererComponent>().Tint = Color(230, 80, 80);

		MainViewportPanel::Create(m_Scene);
		SceneHierarchyPanel::Create(m_Scene);
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
	}

	void EditorLayer::OnEvent(Event& event)
	{
	}
}