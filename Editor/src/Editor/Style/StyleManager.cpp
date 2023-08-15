#include "Editor/Style/StyleManager.h"

StyleManager* StyleManager::s_Instance = nullptr;
void StyleManager::Init()
{
	s_Instance = new StyleManager();
	s_Instance->LoadFonts();
	s_Instance->SetupStyle();
}

void StyleManager::LoadFonts()
{
	ImGuiIO& io = ImGui::GetIO();

	io.IniFilename = "..\\imgui.ini";

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
}

void StyleManager::SetupStyle() // TODO: Get values from config
{
	ImGuiStyle* style = &ImGui::GetStyle();

	style->WindowTitleAlign = ImVec2(0.5, 0.5);
	style->WindowRounding = 8.0f;
	style->FrameRounding = 4.0f;
	style->GrabRounding = 3.0f;
	style->WindowPadding = ImVec2(10, 10);

	style->Colors[ImGuiCol_WindowBg] = ImColor(26, 26, 26, 255);
	style->Colors[ImGuiCol_Border] = ImColor(20, 20, 20, 255);

	style->Colors[ImGuiCol_Text] = ImColor(240, 240, 240);
	style->Colors[ImGuiCol_CheckMark] = ImColor(164, 208, 217);
	style->Colors[ImGuiCol_ResizeGrip] = ImColor(115, 160, 220, 51);
	style->Colors[ImGuiCol_DockingPreview] = ImColor(157, 192, 197);
	style->Colors[ImGuiCol_DragDropTarget] = ImColor(166, 180, 195);
	style->Colors[ImGuiCol_ScrollbarBg] = ImColor(0, 0, 0, 50);

	style->Colors[ImGuiCol_SliderGrab] = ImColor(126, 179, 217);
	style->Colors[ImGuiCol_SliderGrabActive] = ImColor(126, 179, 217, 150);

	style->Colors[ImGuiCol_TitleBg] = ImColor(20, 20, 21);
	style->Colors[ImGuiCol_TitleBgActive] = ImColor(20, 20, 21);

	style->Colors[ImGuiCol_FrameBg] = ImColor(255, 255, 255, 30);
	style->Colors[ImGuiCol_FrameBgHovered] = ImColor(255, 255, 255, 80);
	style->Colors[ImGuiCol_FrameBgActive] = ImColor(48, 48, 48, 150);

	style->Colors[ImGuiCol_Tab] = ImColor(68, 80, 86);
	style->Colors[ImGuiCol_TabHovered] = ImColor(81, 119, 134);
	style->Colors[ImGuiCol_TabActive] = ImColor(48, 49, 51);
	style->Colors[ImGuiCol_TabUnfocused] = ImColor(0, 0, 0, 0);
	style->Colors[ImGuiCol_TabUnfocusedActive] = ImColor(0, 0, 0, 0);

	style->Colors[ImGuiCol_Button] = ImColor(17, 17, 17);
	style->Colors[ImGuiCol_ButtonHovered] = ImColor(100, 150, 200, 180);
	style->Colors[ImGuiCol_ButtonActive] = ImColor(95, 134, 170, 80);

	style->Colors[ImGuiCol_Header] = ImColor(37, 37, 37, 255);
	style->Colors[ImGuiCol_HeaderHovered] = ImColor(48, 48, 48, 255);
	style->Colors[ImGuiCol_HeaderActive] = ImColor(26, 26, 26, 255);

	style->Colors[ImGuiCol_Separator] = ImColor(30, 30, 32, 255);
	style->Colors[ImGuiCol_SeparatorHovered] = ImColor(84, 109, 123, 200);
	style->Colors[ImGuiCol_SeparatorActive] = ImColor(116, 151, 170, 200);

	style->Colors[ImGuiCol_MenuBarBg] = ImColor(20, 20, 21);
}