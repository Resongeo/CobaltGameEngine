#pragma once

#include "Cobalt.h"
using namespace Cobalt;

struct EditorFonts;

class Controls
{
public:
	static void Init();

	static void DrawVector3(const char* label, glm::vec3& values, const ImVec2& offset = { 0, 0 }, float resetValue = 0.0f, float item_width = 80.0f, float speed = 0.05f);
	static void DrawVector2(const char* label, glm::vec2& values, const ImVec2& offset = { 0, 0 }, float resetValue = 0.0f, float item_width = 120.0f, float speed = 0.05f);
	static bool DrawVector1(const char* label, float& value, const ImVec2& offset = { 0, 0 }, float resetValue = 0.0f, float min = 0.0f, float max = 0.0f, float item_width = 180.0f, float label_width = 60.0f, float speed = 0.05f);

	static void DrawRect(ImVec2 cursor_pos, ImVec2 content_region, float height, ImU32 color, float radius = 0.0f);
	static void DrawRectOutlined(ImVec2 cursor_pos, ImVec2 content_region, float height, ImU32 color, float outlineWidth, ImU32 outlineColor, float radius = 0.0f);

	static void DrawImageRounded(ImTextureID textureID, const ImVec2& posMin, const ImVec2& posMax, const ImVec2& uvMin, const ImVec2& uvMax, float radius);

private:
	static inline void SetOffset(const ImVec2& offset)
	{
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offset.x);
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + offset.y);
	}

private:
	static Controls* s_Instance;
	EditorFonts* m_EditorFonts;
};