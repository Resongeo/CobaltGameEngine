#include "Editor/Utils/Controls.h"
#include "Editor/Style/StyleManager.h"

Controls* Controls::s_Instance = nullptr;
void Controls::Init()
{
	s_Instance = new Controls();
	s_Instance->m_EditorFonts = StyleManager::GetEditorFonts();
}

void Controls::DrawVector3(const char* label, glm::vec3& values, float resetValue, float item_width, float speed)
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

	ImGui::PushID(label);
	ImGui::Columns(2);

	ImGui::SetColumnWidth(0, 100.f);
	ImGui::PushFont(s_Instance->m_EditorFonts->SemiBold);
	ImGui::Text(label);
	ImGui::PopFont();

	ImGui::NextColumn();

	ImGui::SetNextItemWidth(item_width);

	ImGui::DragFloat(xLabel, &values.x, speed);
	if (ImGui::IsItemActive() && Input::GetMouseButtonDown(1))
		values.x = resetValue;
	else if (ImGui::IsItemClicked(1))
		values.x = resetValue;

	ImGui::SameLine();

	ImGui::SetNextItemWidth(item_width);

	ImGui::DragFloat(yLabel, &values.y, speed);
	if (ImGui::IsItemActive() && Input::GetMouseButtonDown(1))
		values.y = resetValue;
	else if (ImGui::IsItemClicked(1))
		values.y = resetValue;

	ImGui::SameLine();

	ImGui::SetNextItemWidth(item_width);

	ImGui::DragFloat(zLabel, &values.z, speed);
	if (ImGui::IsItemActive() && Input::GetMouseButtonDown(1))
		values.z = resetValue;
	else if (ImGui::IsItemClicked(1))
		values.z = resetValue;

	ImGui::Columns(1);
	ImGui::PopID();
}

void Controls::DrawVector2(const char* label, glm::vec2& values, float resetValue, float item_width, float speed)
{
	const char* xLabel;
	const char* yLabel;

	if (Input::GetKeyDown(KEYCODE_LEFT_SHIFT))
	{
		xLabel = "##multiEdit";
		yLabel = "##multiEdit";

		speed /= 10.0f;
	}
	else
	{
		xLabel = "##X";
		yLabel = "##Y";
	}

	ImGui::PushID(label);
	ImGui::Columns(2);

	ImGui::SetColumnWidth(0, 100.f);
	ImGui::PushFont(s_Instance->m_EditorFonts->SemiBold);
	ImGui::Text(label);
	ImGui::PopFont();

	ImGui::NextColumn();

	ImGui::SetNextItemWidth(item_width);

	ImGui::DragFloat(xLabel, &values.x, speed);
	if (ImGui::IsItemActive() && Input::GetMouseButtonDown(1))
		values.x = resetValue;
	else if (ImGui::IsItemClicked(1))
		values.x = resetValue;

	ImGui::SameLine();

	ImGui::SetNextItemWidth(item_width);

	ImGui::DragFloat(yLabel, &values.y, speed);
	if (ImGui::IsItemActive() && Input::GetMouseButtonDown(1))
		values.y = resetValue;
	else if (ImGui::IsItemClicked(1))
		values.y = resetValue;

	ImGui::Columns(1);
	ImGui::PopID();
}

bool Controls::DrawVector1(const char* label, float& value, float resetValue, float min, float max, float item_width, float label_width, float speed)
{
	ImGui::PushID(label);
	ImGui::Columns(2);

	ImGui::SetColumnWidth(0, label_width);
	ImGui::PushFont(s_Instance->m_EditorFonts->SemiBold);
	ImGui::Text(label);
	ImGui::PopFont();

	ImGui::NextColumn();

	ImGui::SetNextItemWidth(item_width);

	bool interact = ImGui::DragFloat("##X", std::addressof(value), speed, min, max);
	if (ImGui::IsItemActive() && Input::GetMouseButtonDown(1))
	{
		value = resetValue;
		interact = true;
	}
	else if (ImGui::IsItemClicked(1))
	{
		value = resetValue;
		interact = true;
	}

	ImGui::Columns(1);
	ImGui::PopID();

	return interact;
}