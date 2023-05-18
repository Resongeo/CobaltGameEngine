#include "Editor/Panels/Components/ComponentsPanel.h"
#include "Editor/Panels/Scene/SceneHierarchyPanel.h"
#include "Editor/Utils/Controls.h"

ComponentsPanel::ComponentsPanel() : EditorPanel("Components panel") { }

void ComponentsPanel::Update()
{
	Entity selectedEntity = SceneHierarchyPanel::GetSelectedEntity();

	ImGui::Begin(ICON_TASKS " Components");

	if (selectedEntity)
		DrawComponents(selectedEntity);

	ImGui::End();
}

void ComponentsPanel::DrawComponents(Entity entity)
{
	ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;

	ImGui::PushFont(p_EditorFonts->SemiBold);
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 5, 5 });

	ImGui::PushStyleColor(ImGuiCol_Text, { 0.34, 0.68, 0.96, 1.0 });
	if (ImGui::TreeNodeEx(ICON_TAG " Tag Component", treeNodeFlags))
	{
		ImGui::PushStyleColor(ImGuiCol_Text, { 0.94, 0.94, 0.94, 1.0 });
		ImGui::PushFont(p_EditorFonts->Regular);

		auto& tag = entity.GetComponent<TagComponent>();

		ImGui::PushFont(p_EditorFonts->SemiBold);
		ImGui::Text("Tag");
		ImGui::PopFont();
		
		ImGui::SameLine();
		ImGui::InputText("##Tag", tag.Tag.data(), tag.Tag.capacity());

		ImGui::PopFont();
		ImGui::TreePop();
		ImGui::PopStyleColor();
	}
	ImGui::PopStyleColor();

	ImGui::Dummy(ImVec2(0, 10));

	ImGui::PushStyleColor(ImGuiCol_Text, { 0.96 ,0.65, 0.34, 1.0 });
	if (ImGui::TreeNodeEx(ICON_TH " Transform Component", treeNodeFlags))
	{
		ImGui::PushStyleColor(ImGuiCol_Text, { 0.94, 0.94, 0.94, 1.0 });
		ImGui::PushFont(p_EditorFonts->Regular);

		auto& transform = entity.GetComponent<TransformComponent>();
		Controls::DrawVector3("Position", transform.Position);
		Controls::DrawVector3("Rotation", transform.Rotation);
		Controls::DrawVector3("Scale", transform.Scale, 1.0f);

		ImGui::PopFont();
		ImGui::TreePop();
		ImGui::PopStyleColor();
	}
	ImGui::PopStyleColor();

	if (entity.HasComponent<SpriteRendererComponent>())
	{
		bool remove = false;
		ImGui::Dummy(ImVec2(0, 10));

		ImGui::PushStyleColor(ImGuiCol_Text, { 0.97, 0.66, 0.96, 1.0 });
		if (ImGui::TreeNodeEx(ICON_IMAGE " Sprite Renderer Component", treeNodeFlags))
		{
			ImGui::SameLine();
			ImGui::SetCursorPosX(ImGui::GetWindowContentRegionWidth() - 10);
			ImGui::PushStyleColor(ImGuiCol_Text, { 1.0, 1.0, 1.0, 1.0 });
			ImGui::PushStyleColor(ImGuiCol_Button, { 1.0, 1.0, 1.0, 0.0 });
			if (ImGui::Button(ICON_TIMES_CIRCLE)) remove = true;
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();

			ImGui::PushStyleColor(ImGuiCol_Text, { 0.94, 0.94, 0.94, 1.0 });
			ImGui::PushFont(p_EditorFonts->Regular);

			auto& spriteRenderer = entity.GetComponent<SpriteRendererComponent>();

			if (spriteRenderer.Texture)
			{
				ImGui::Text(spriteRenderer.Texture->GetPath().c_str());
				ImGui::SameLine();
				ImGui::Image((ImTextureID)spriteRenderer.Texture->GetID(), ImVec2(100, 100), { 0, 1 }, { 1, 0 });
			}
			else
			{
				ImGui::Text("Default White texture");
			}

			ImGui::Dummy({ 0, 5 });

			ImGui::ColorPicker4("Preview", glm::value_ptr(spriteRenderer.Color), ImGuiColorEditFlags_NoSmallPreview);

			ImGui::Dummy({ 0, 5 });

			Controls::DrawVector2("Tiling", spriteRenderer.Tiling, 1.0f);

			ImGui::PopFont();
			ImGui::TreePop();
			ImGui::PopStyleColor();
		}
		ImGui::PopStyleColor();

		if (remove) entity.RemoveComponent<SpriteRendererComponent>();
	}

	ImGui::PopFont();
	ImGui::PopStyleVar();
}