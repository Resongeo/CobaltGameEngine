#include "pch.h"
#include "CobaltEditor/Core/EditorLayer.h"
#include "CobaltEditor/Components/DockSpace.h"
#include "CobaltEditor/Managers/EditorPanelManager.h"
#include "CobaltEditor/Panels/MainViewportPanel.h"
#include "CobaltEditor/Panels/SceneHierarchyPanel.h"

#include "CobaltEditor/Core/Codepoints.h"

namespace CobaltEditor
{
	void EditorLayer::OnAttach()
	{
		ImGuiIO& io = ImGui::GetIO();
		io.IniFilename = "..\\imgui.ini";

		float baseFontSize = 18.0f;
		float iconFontSize = baseFontSize * 2.0f / 3.0f;

		ImFontConfig fontConfig;
		fontConfig.MergeMode = true;
		fontConfig.PixelSnapH = true;
		fontConfig.GlyphMinAdvanceX = iconFontSize;
		fontConfig.GlyphOffset = { 0, 2 };
		static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };

		io.FontDefault = io.Fonts->AddFontFromFileTTF("..\\assets\\fonts\\JetBrainsMono-Regular.ttf", baseFontSize);
		io.Fonts->AddFontFromFileTTF("..\\assets\\fonts\\" FONT_ICON_FILE_NAME_FAS, baseFontSize, &fontConfig, icon_ranges);

		/*
		
		float baseFontSize = 20.0f; // TODO: Get values from config
		float iconFontSize = baseFontSize * 2.0f / 3.0f;

		ImFontConfig config;
		config.MergeMode = true;
		config.PixelSnapH = true;
		config.GlyphMinAdvanceX = iconFontSize;
		config.GlyphOffset = { 0, 2 };
		static const ImWchar icon_ranges[] = { ICON_MIN, ICON_MAX, 0 };

		m_EditorFonts.Regular = io.Fonts->AddFontFromFileTTF("..\\assets\\fonts\\JetBrainsMono-Regular.ttf", baseFontSize);
		io.Fonts->AddFontFromFileTTF("..\\assets\\fonts\\forkawesome-webfont.ttf", baseFontSize, &config, icon_ranges);

		m_EditorFonts.SemiBold = io.Fonts->AddFontFromFileTTF("..\\assets\\fonts\\JetBrainsMono-Bold.ttf", baseFontSize);
		io.Fonts->AddFontFromFileTTF("..\\assets\\fonts\\forkawesome-webfont.ttf", baseFontSize, &config, icon_ranges);
		*/

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