#pragma once

#include "Cobalt.h"
using namespace Cobalt;

namespace CobaltEditor
{
	namespace MouseUtils
	{
		inline bool Intersect(const ImVec2& min, const ImVec2& max)
		{
			auto mousePos = ImGui::GetMousePos();
			return mousePos.x >= min.x && mousePos.x <= max.x && mousePos.y >= min.y && mousePos.y <= max.y;
		}

		inline bool Intersect(const Vec2& min, const Vec2& max)
		{
			auto mousePos = ImGui::GetMousePos();
			return mousePos.x >= min.x && mousePos.x <= max.x && mousePos.y >= min.y && mousePos.y <= max.y;
		}
	}
}