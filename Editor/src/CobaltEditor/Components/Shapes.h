#pragma once

#include "Cobalt.h"
using namespace Cobalt;

namespace CobaltEditor
{
	namespace Shapes
	{
		inline void DrawRect(const ImVec2& min, const ImVec2& max, const Color& col, float radius = 0.0f)
		{
			auto* drawList = ImGui::GetWindowDrawList();
			drawList->AddRectFilled(min, max, col, radius);
		}

		inline void DrawRectOutlined(const ImVec2& min, const ImVec2& max, const Color& bgColor, const Color& outlineColor, float radius = 0.0f, float thickness = 6.0f)
		{
			auto* drawList = ImGui::GetWindowDrawList();
			drawList->AddRectFilled(min, max, outlineColor, radius);
			drawList->AddRectFilled(
				{ min.x + thickness * 0.5f, min.y + thickness * 0.5f },
				{ max.x - thickness * 0.5f, max.y - thickness * 0.5f },
				bgColor, radius);
		}
	}
}