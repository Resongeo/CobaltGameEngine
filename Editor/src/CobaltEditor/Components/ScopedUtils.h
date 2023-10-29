#pragma once

#include "Cobalt.h"

namespace CobaltEditor
{
	class ScopedID
	{
	public:
		ScopedID(int id)
		{
			ImGui::PushID(id);
		}

		ScopedID(const char* id)
		{
			ImGui::PushID(id);
		}

		ScopedID(const void* id)
		{
			ImGui::PushID(id);
		}

		ScopedID(const char* begin, const char* end)
		{
			ImGui::PushID(begin, end);
		}

		~ScopedID()
		{
			ImGui::PopID();
		}
	};

	class ScopedStyleVar
	{
	public:
		ScopedStyleVar(ImGuiStyleVar idx, float value)
		{
			ImGui::PushStyleVar(idx, value);
		}

		ScopedStyleVar(ImGuiStyleVar idx, const ImVec2& value)
		{
			ImGui::PushStyleVar(idx, value);
		}

		~ScopedStyleVar()
		{
			ImGui::PopStyleVar();
		}
	};
}