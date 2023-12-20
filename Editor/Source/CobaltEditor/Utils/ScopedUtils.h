#pragma once

#include "Cobalt.h"
using namespace Cobalt;

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

	class ScopedFont
	{
	public:
		ScopedFont(ImFont* font)
		{
			ImGui::PushFont(font);
		}

		~ScopedFont()
		{
			ImGui::PopFont();
		}
	};

	class ScopedColor
	{
	public:
		ScopedColor(ImGuiCol idx, const Color& color)
		{
			ImGui::PushStyleColor(idx, (ImU32)color);
		}

		~ScopedColor()
		{
			ImGui::PopStyleColor();
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

	struct StyleVar
	{
		ImGuiStyleVar Idx;
		
		union
		{
			float floatValue;
			ImVec2 imVec2Value;
		};

		bool SingleValue;

		StyleVar(ImGuiStyleVar idx, float value) : Idx(idx), floatValue(value), SingleValue(true) { }
		StyleVar(ImGuiStyleVar idx, const ImVec2& value) : Idx(idx), imVec2Value(value), SingleValue(false) { }
	};

	class ScopedStyleVars
	{
	public:
		ScopedStyleVars(InitializerList<StyleVar> styleVars) : m_StyleVars(styleVars)
		{
			for (auto& style : m_StyleVars)
			{
				switch (style.SingleValue)
				{
					case true:
						ImGui::PushStyleVar(style.Idx, style.floatValue);
						break;
					case false:
						ImGui::PushStyleVar(style.Idx, style.imVec2Value);
						break;
				}
			}
		}

		~ScopedStyleVars()
		{
			ImGui::PopStyleVar(m_StyleVars.size());
		}

	private:
		Vector<StyleVar> m_StyleVars;
	};
}