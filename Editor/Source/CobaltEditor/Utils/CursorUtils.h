#pragma once

#include "Cobalt.h"
using namespace Cobalt;

namespace CobaltEditor
{
	namespace CursorUtils
	{
		inline void Translate(float x, float y)
		{
			auto current = ImGui::GetCursorPos();
			ImGui::SetCursorPos({ current.x + x, current.y + y });
		}

		inline void Translate(const Vec2& offset)
		{
			auto current = ImGui::GetCursorPos();
			ImGui::SetCursorPos({ current.x + offset.x, current.y + offset.y });
		}
	}
}