#include "pch.h"
#include "CobaltEditor/Core/Codepoints.h"
#include "CobaltEditor/Managers/StyleManager.h"

namespace CobaltEditor
{
	StyleManager* StyleManager::s_Instance = nullptr;

	void StyleManager::Init()
	{
		s_Instance = new StyleManager();
	}

	void StyleManager::LoadFonts()
	{
		ImGuiIO& io = ImGui::GetIO();

		const float baseFontSize = 18.0f;
		const float iconFontSize = baseFontSize * 2.0f / 3.0f;

		ImFontConfig fontConfig;
		fontConfig.MergeMode = true;
		fontConfig.PixelSnapH = true;
		fontConfig.GlyphMinAdvanceX = iconFontSize;
		fontConfig.GlyphOffset = { 0, 2 };
		static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };

		s_Instance->m_Fonts.Regular = io.Fonts->AddFontFromFileTTF("Assets\\fonts\\JetBrainsMono-Regular.ttf", baseFontSize);
		io.Fonts->AddFontFromFileTTF("Assets\\fonts\\" FONT_ICON_FILE_NAME_FAS, iconFontSize, &fontConfig, icon_ranges);

		s_Instance->m_Fonts.SemiBold = io.Fonts->AddFontFromFileTTF("Assets\\fonts\\JetBrainsMono-Bold.ttf", baseFontSize);
		io.Fonts->AddFontFromFileTTF("Assets\\fonts\\" FONT_ICON_FILE_NAME_FAS, iconFontSize + 2.0f, &fontConfig, icon_ranges);

		io.FontDefault = s_Instance->m_Fonts.Regular;
	}

	void StyleManager::LoadStyle()
	{
		ImGuiStyle* style = &ImGui::GetStyle();

		style->WindowTitleAlign = ImVec2(0.5, 0.5);
		style->WindowRounding = 6.0f;
		style->FrameRounding = 3.0f;
		style->GrabRounding = 3.0f;

		style->Colors[ImGuiCol_Text] = Color(240);
		style->Colors[ImGuiCol_CheckMark] = Color(164, 208, 217);
		style->Colors[ImGuiCol_Button] = Color(0);
		style->Colors[ImGuiCol_ButtonHovered] = Color(35);
		style->Colors[ImGuiCol_ButtonActive] = Color(70);

		style->Colors[ImGuiCol_WindowBg] = Color(23);
		style->Colors[ImGuiCol_Border] = Color(45, 57, 74, 128);
		style->Colors[ImGuiCol_DockingPreview] = Color(210, 230, 255, 150);

		style->Colors[ImGuiCol_TitleBg] = Color(21);
		style->Colors[ImGuiCol_TitleBgActive] = Color(18);

		style->Colors[ImGuiCol_FrameBg] = Color(46);
		style->Colors[ImGuiCol_FrameBgHovered] = Color(46, 160);
		style->Colors[ImGuiCol_FrameBgActive] = Color(88);

		style->Colors[ImGuiCol_SliderGrab] = Color(150, 168, 179);
		style->Colors[ImGuiCol_SliderGrabActive] = Color(164, 208, 217);

		style->Colors[ImGuiCol_ResizeGrip] = Color(45, 57, 74, 128);
		style->Colors[ImGuiCol_ResizeGripHovered] = Color(164, 208, 217, 85);
		style->Colors[ImGuiCol_ResizeGripActive] = Color(164, 208, 217, 85);

		style->Colors[ImGuiCol_Header] = Color(54);
		style->Colors[ImGuiCol_HeaderHovered] = Color(54, 160);
		style->Colors[ImGuiCol_HeaderActive] = Color(88);

		style->Colors[ImGuiCol_Separator] = Color(31);
		style->Colors[ImGuiCol_SeparatorHovered] = Color(164, 208, 217, 85);
		style->Colors[ImGuiCol_SeparatorActive] = Color(164, 208, 217, 85);

		style->Colors[ImGuiCol_Tab] = Color(23);
		style->Colors[ImGuiCol_TabHovered] = Color(45);
		style->Colors[ImGuiCol_TabActive] = Color(60);
		style->Colors[ImGuiCol_TabUnfocused] = Color(23);
		style->Colors[ImGuiCol_TabUnfocusedActive] = Color(23);
	}
}