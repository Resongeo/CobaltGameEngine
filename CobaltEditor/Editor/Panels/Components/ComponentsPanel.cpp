#include "Editor/Panels/Components/ComponentsPanel.h"
#include "Editor/Panels/Scene/SceneHierarchyPanel.h"

#include "Editor/CobaltEditor.h"

ComponentsPanel::ComponentsPanel() : EditorPanel("Components panel")
{
	LOG_TRACE("{0} created!", m_PanelName);
}

void ComponentsPanel::Update()
{
	Entity selectedEntity = SceneHierarchyPanel::GetSelectedEntity();


	ImGui::Begin("Components");

	if (selectedEntity)
	{
		DrawComponents(selectedEntity);
	}

	ImGui::End();
}

void ComponentsPanel::DrawComponents(Entity entity)
{
	ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;

	EditorFonts editorfonts = CobaltEditor::Get().GetEditorLayer()->GetEditorFonts();
	m_Boldfont = editorfonts.SemiBold;
	m_Regularfont = editorfonts.Regular;

	ImGui::PushFont(m_Boldfont);
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 5, 5 });

	if (ImGui::TreeNodeEx("Tag Component", treeNodeFlags))
	{
		ImGui::PushFont(m_Regularfont);

		auto& tag = entity.GetComponent<TagComponent>();

		ImGui::PushFont(m_Boldfont);
		ImGui::Text("Tag");
		ImGui::PopFont();
		
		ImGui::SameLine();
		ImGui::InputText("##Tag", tag.Tag.data(), tag.Tag.capacity());

		ImGui::PopFont();
		ImGui::TreePop();
	}

	ImGui::Dummy(ImVec2(0, 10));

	if (ImGui::TreeNodeEx("Transform Component", treeNodeFlags))
	{
		ImGui::PushFont(m_Regularfont);

		auto& transform = entity.GetComponent<TransformComponent>();
		DrawVector3("Position", transform.Position);
		DrawVector3("Rotation", transform.Rotation);
		DrawVector3("Scale", transform.Scale, 1.0f);

		ImGui::PopFont();
		ImGui::TreePop();
	}


	if (entity.HasComponent<SpriteRendererComponent>())
	{
		ImGui::Dummy(ImVec2(0, 10));

		if (ImGui::TreeNodeEx("Sprite Renderer Component", treeNodeFlags))
		{
			ImGui::PushFont(m_Regularfont);

			auto& spriteRenderer = entity.GetComponent<SpriteRendererComponent>();

			if (spriteRenderer.Sprite)
			{
				ImGui::Text(spriteRenderer.Sprite->GetPath().c_str());
				ImGui::SameLine();
				ImGui::Image((ImTextureID)spriteRenderer.Sprite->GetID(), ImVec2(100, 100), { 0, 1 }, { 1, 0 });
			}
			else
			{
				ImGui::Text("Default White texture");
			}

			ImGui::Dummy({ 0, 5 });

			ImGui::ColorPicker4("Preview", glm::value_ptr(spriteRenderer.Color), ImGuiColorEditFlags_NoSmallPreview);

			ImGui::Dummy({ 0, 5 });

			DrawVector2("Tiling", spriteRenderer.Tiling, 1.0f);

			ImGui::PopFont();
			ImGui::TreePop();
		}
	}

	ImGui::PopFont();
	ImGui::PopStyleVar();
}

void ComponentsPanel::DrawVector3(const char* label, glm::vec3& values, float resetValue, float item_width, float speed)
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
	ImGui::PushFont(m_Boldfont);
	ImGui::Text(label);
	ImGui::PopFont();

	ImGui::NextColumn();

	ImGui::SetNextItemWidth(item_width);

	ImGui::DragFloat(xLabel, &values.x, speed);
	if (ImGui::IsItemActive() && Input::GetMouseButtonDown(1))
		values.x = resetValue;
	else if(ImGui::IsItemClicked(1))
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

void ComponentsPanel::DrawVector2(const char* label, glm::vec2& values, float resetValue, float item_width, float speed)
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
	ImGui::PushFont(m_Boldfont);
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