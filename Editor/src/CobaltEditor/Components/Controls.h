#pragma once

#include "Cobalt.h"
using namespace Cobalt;

#include "CobaltEditor/Utils/CursorUtils.h"
#include "CobaltEditor/Utils/ScopedUtils.h"

namespace CobaltEditor
{
	namespace Controls
	{
		inline void Vector3(const char* label, Vec3& value, float reset = 0.0f, float speed = 0.1f, float labelWidth = 100.0f, float contentWidth = -1.0f, const Vec2& offset = Vec2(0, 0), float leftMargin = 0.0f)
		{
			const char* xLabel;
			const char* yLabel;
			const char* zLabel;

			if (Input::GetKeyDown(KEYCODE_LEFT_SHIFT))
			{
				xLabel = "##multiEdit";
				yLabel = "##multiEdit";
				zLabel = "##multiEdit";

				speed /= 10.0f;
			}
			else
			{
				xLabel = "##X";
				yLabel = "##Y";
				zLabel = "##Z";
			}

			ScopedID _(label);
			ImGui::Columns(2);

			ImGui::SetColumnWidth(0, labelWidth);
			CursorUtils::Translate(offset);
			ImGui::Text(label);

			ImGui::NextColumn();
			auto itemWidth = contentWidth <= 0.0f ? ImGui::GetContentRegionAvail().x / 3.0f : contentWidth;
			ImGui::SetNextItemWidth(itemWidth - leftMargin);

			ImGui::DragFloat(xLabel, &value.x, speed);
			if (ImGui::IsItemActive() && Input::GetMouseButtonDown(1))
			{
				value.x = reset;
			}
			else if (ImGui::IsItemClicked(1))
			{
				value.x = reset;
			}

			ImGui::SameLine();
			ImGui::SetNextItemWidth(itemWidth - leftMargin);

			ImGui::DragFloat(yLabel, &value.y, speed);
			if (ImGui::IsItemActive() && Input::GetMouseButtonDown(1))
			{
				value.y = reset;
			}
			else if (ImGui::IsItemClicked(1))
			{
				value.y = reset;
			}

			ImGui::SameLine();
			ImGui::SetNextItemWidth(itemWidth - leftMargin);

			ImGui::DragFloat(zLabel, &value.z, speed);
			if (ImGui::IsItemActive() && Input::GetMouseButtonDown(1))
			{
				value.z = reset;
			}
			else if (ImGui::IsItemClicked(1))
			{
				value.z = reset;
			}

			ImGui::Columns(1);
		}
	}
}