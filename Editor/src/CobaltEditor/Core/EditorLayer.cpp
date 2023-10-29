#include "CobaltEditor/Core/EditorLayer.h"
#include "CobaltEditor/Components/DockSpace.h"
#include "CobaltEditor/Managers/EditorPanelManager.h"

#include "CobaltEditor/Panels/MainViewportPanel.h"

namespace CobaltEditor
{
	void EditorLayer::OnAttach()
	{
		ImGuiIO& io = ImGui::GetIO();
		io.IniFilename = "..\\imgui.ini";

		m_Window = Cobalt::Application::GetWindow();
		m_Scene = CreateRef<Cobalt::Scene>("Scene");
		auto entity = m_Scene->CreateEntity();
		entity.AddComponent<Cobalt::SpriteRendererComponent>().Tint = Cobalt::Color(230, 80, 80);

		MainViewportPanel::Create(m_Scene);
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

	void EditorLayer::OnEvent(Cobalt::Event& event)
	{
	}
}