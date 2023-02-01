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
	ImFont* boldfont = editorfonts.SemiBold;
	ImFont* regularfont = editorfonts.Regular;

	ImGui::PushFont(boldfont);
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 5, 5 });

	if (ImGui::TreeNodeEx("Tag Component", treeNodeFlags))
	{
		ImGui::PushFont(regularfont);

		auto& tag = entity.GetComponent<TagComponent>();
		ImGui::Text("Tag");
		ImGui::SameLine();
		ImGui::InputText("##Tag", tag.Tag.data(), tag.Tag.capacity());

		ImGui::PopFont();
		ImGui::TreePop();
	}

	ImGui::Dummy(ImVec2(0, 10));

	if (ImGui::TreeNodeEx("Transform Component", treeNodeFlags))
	{
		ImGui::PushFont(regularfont);

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
			ImGui::PushFont(regularfont);

			auto& spriteRenderer = entity.GetComponent<SpriteRendererComponent>();
			ImGui::Image((ImTextureID)spriteRenderer.Sprite->GetID(), ImVec2(100, 100), { 0, 1 }, { 1, 0 });
			ImGui::ColorEdit4("Sprite Color", glm::value_ptr(spriteRenderer.Color));

			ImGui::PopFont();
			ImGui::TreePop();
		}
	}

	ImGui::PopFont();
	ImGui::PopStyleVar();
}

void ComponentsPanel::DrawVector3(const std::string& label, glm::vec3& values, float resetValue, float item_width, float speed)
{
	ImGui::PushID(label.c_str());
	ImGui::Columns(2);
	
	ImGui::SetColumnWidth(0, 100.f);
	ImGui::Text(label.c_str());

	ImGui::NextColumn();

	ImGui::SetNextItemWidth(item_width);
	const char* xLabel = Input::GetKeyDown(KEYCODE_LEFT_SHIFT) ? "##multiEdit" : "##X";

	ImGui::DragFloat(xLabel, &values.x, speed);
	if (ImGui::IsItemActive() && Input::GetMouseButtonDown(1))
		values.x = resetValue;
	else if(ImGui::IsItemClicked(1))
		values.x = resetValue;

	ImGui::SameLine();

	ImGui::SetNextItemWidth(item_width);
	const char* yLabel = Input::GetKeyDown(KEYCODE_LEFT_SHIFT) ? "##multiEdit" : "##Y";

	ImGui::DragFloat(yLabel, &values.y, speed);
	if (ImGui::IsItemActive() && Input::GetMouseButtonDown(1))
		values.y = resetValue;
	else if (ImGui::IsItemClicked(1))
		values.y = resetValue;

	ImGui::SameLine();

	ImGui::SetNextItemWidth(item_width);
	const char* zLabel = Input::GetKeyDown(KEYCODE_LEFT_SHIFT) ? "##multiEdit" : "##Z";

	ImGui::DragFloat(zLabel, &values.z, speed);
	if (ImGui::IsItemActive() && Input::GetMouseButtonDown(1))
		values.z = resetValue;
	else if (ImGui::IsItemClicked(1))
		values.z = resetValue;

	ImGui::Columns(1);
	ImGui::PopID();
}
