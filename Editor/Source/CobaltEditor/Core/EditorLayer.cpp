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

		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& event)
	{
		EditorPanelManager::OnEvent(event);

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<LogEvent>(BIND_EVENT_FN(EditorLayer::OnLogEvent));
	}

	bool EditorLayer::OnLogEvent(LogEvent e)
	{
		auto message = e.GetLogMessage();
		switch (e.GetLogType())
		{
			case LogEventType::Trace: Log::Trace("{}", message); break;
			case LogEventType::Info: Log::Info("{}", message); break;
			case LogEventType::Warn: Log::Warn("{}", message); break;
			case LogEventType::Error: Log::Error("{}", message); break;
		}

		return true;
	}
}