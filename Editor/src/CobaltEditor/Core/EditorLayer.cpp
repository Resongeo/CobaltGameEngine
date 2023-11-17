#include "pch.h"
#include "CobaltEditor/Core/EditorLayer.h"
#include "CobaltEditor/Components/DockSpace.h"
#include "CobaltEditor/Managers/EditorPanelManager.h"
#include "CobaltEditor/Panels/ComponentsPanel.h"
#include "CobaltEditor/Panels/MainViewportPanel.h"
#include "CobaltEditor/Panels/SceneHierarchyPanel.h"
#include "CobaltEditor/Panels/LogPanel.h"

#include "CobaltEditor/Logger/Log.h"

#include "CobaltEditor/Core/Codepoints.h"

namespace CobaltEditor
{
	void EditorLayer::OnAttach()
	{
		m_Window = Application::GetWindow();

		ImGuiIO& io = ImGui::GetIO();
		io.IniFilename = "..\\imgui.ini";

		const float baseFontSize = 18.0f;
		const float iconFontSize = baseFontSize * 2.0f / 3.0f;

		ImFontConfig fontConfig;
		fontConfig.MergeMode = true;
		fontConfig.PixelSnapH = true;
		fontConfig.GlyphMinAdvanceX = iconFontSize;
		fontConfig.GlyphOffset = { 0, 2 };
		static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };

		io.FontDefault = io.Fonts->AddFontFromFileTTF("..\\assets\\fonts\\JetBrainsMono-Regular.ttf", baseFontSize);
		io.Fonts->AddFontFromFileTTF("..\\assets\\fonts\\" FONT_ICON_FILE_NAME_FAS, baseFontSize, &fontConfig, icon_ranges);

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
		if (ImGui::Button("Add Logs"))
		{
			Log::Trace("Trace message");
			Log::Info("Info message");
			Log::Warn("Warn message");
			Log::Error("Error message");
		}
		ImGui::End();

		ImGui::ShowDemoWindow();
	}

	void EditorLayer::OnEvent(Event& event)
	{
	}
}