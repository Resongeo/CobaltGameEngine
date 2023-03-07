#pragma once

#include "Cobalt.h"
using namespace Cobalt;

struct EditorFonts;

class Controls
{
public:
	static void Init();

	static void DrawVector3(const char* label, glm::vec3& values, float resetValue = 0.0f, float item_width = 80.0f, float speed = 0.05f);
	static void DrawVector2(const char* label, glm::vec2& values, float resetValue = 0.0f, float item_width = 120.0f, float speed = 0.05f);
	static bool DrawVector1(const char* label, float& value, float resetValue = 0.0f, float min = 0.0f, float max = 0.0f, float item_width = 180.0f, float label_width = 60.0f, float speed = 0.05f);

private:
	static Controls* s_Instance;
	EditorFonts* m_EditorFonts;
};