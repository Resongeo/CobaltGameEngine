#include "Editor/Panels/Components/ComponentsPanel.h"
#include "Editor/Panels/Scene/SceneHierarchyPanel.h"
#include "Editor/Utils/Controls.h"

ComponentsPanel::ComponentsPanel() : EditorPanel(ICON_TASKS " Components") { }

void ComponentsPanel::Update()
{
	m_SelectedEntity = SceneHierarchyPanel::GetSelectedEntity();
}

void ComponentsPanel::ImGuiUpdate()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 5, 10 });
	ImGui::Begin(GetName());

	if (m_SelectedEntity)
		DrawComponents(m_SelectedEntity);

	ImGui::End();
	ImGui::PopStyleVar();
}

template<typename T, typename ComponentSettings>
static void DrawComponent(const char* title, Entity entity, bool& opened, const Color& primaryColor, float height, EditorFonts* editorFonts, ComponentSettings componentSettings)
{
	if (entity.HasComponent<T>())
	{
		ImVec2 cursorPos = ImGui::GetCursorScreenPos();
		ImVec2 contentMax = ImGui::GetContentRegionAvail();

		Color bgCol(28, 28, 28);
		Color inactiveCol(150, 150, 150, 180);

		if (!opened)
		{
			Controls::DrawRectOutlined(cursorPos, contentMax, 25, bgCol, 1, inactiveCol, 6.0f);
		}
		else
		{
			Controls::DrawRectOutlined(cursorPos, contentMax, height, bgCol, 1, primaryColor, 6.0f);
		}

		ImGui::PushStyleColor(ImGuiCol_Text, opened ? (ImU32)primaryColor : (ImU32)inactiveCol);
		ImGui::PushStyleColor(ImGuiCol_Button, (ImU32)Color(0.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImU32)Color(0.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImU32)Color(0.0f));
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10);
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
		ImGui::SetNextItemWidth(contentMax.x - 20);
		ImGui::Text(title);
		ImGui::PopStyleColor(4);

		ImVec2 mousePos = ImGui::GetMousePos();
		if (ImGui::IsMouseClicked(0))
		{
			if (mousePos.x > cursorPos.x && mousePos.x < cursorPos.x + contentMax.x && mousePos.y > cursorPos.y - 4.5f && mousePos.y < cursorPos.y + 25)
			{
				opened = !opened;
			}
		}

		if (opened)
		{
			ImGui::PushStyleColor(ImGuiCol_Text, { 0.94f, 0.94f, 0.94f, 1.0f });
			ImGui::PushFont(editorFonts->Regular);

			auto& component = entity.GetComponent<T>();
			componentSettings(component, editorFonts);

			ImGui::PopFont();
			ImGui::PopStyleColor();

			ImGui::Dummy({ 0, 20 });
		}
		else
		{
			ImGui::Dummy({ 0, 15 });
		}
	}
}

void ComponentsPanel::DrawComponents(Entity entity)
{
	ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;

	ImGui::PushFont(p_EditorFonts->SemiBold);

	DrawComponent<TagComponent>(ICON_TAG " Tag Component", entity, m_TagOpened, m_TagPrimaryColor, 65.0f, p_EditorFonts, [](auto& component, EditorFonts* editorFonts)
	{
		ImGui::Dummy({ 0, 5 });
		ImGui::PushFont(editorFonts->SemiBold);
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 20);
		ImGui::Text("Tag");
		ImGui::PopFont();

		ImGui::SameLine();
		ImGui::InputText("##Tag", component.Tag.data(), component.Tag.capacity());
	});

	DrawComponent<TransformComponent>(ICON_TH " Transform Component", entity, m_TransformOpened, m_TransformPrimaryColor, 125.0f, p_EditorFonts, [](auto& component, EditorFonts* editorFonts)
	{
		ImVec2 offset = { 20, 0 };
		ImGui::Dummy({ 0, 5 });
		Controls::DrawVector3("Position", component.Position, offset);
		Controls::DrawVector3("Rotation", component.Rotation, offset);
		Controls::DrawVector3("Scale", component.Scale, offset, 1.0f);
	});

	DrawComponent<SpriteRendererComponent>(ICON_IMAGE " Sprite Renderer Component", entity, m_SpriteOpened, m_SpritePrimaryColor, 480.0f, p_EditorFonts, [](auto& component, EditorFonts* editorFonts)
	{
		ImVec2 offset = { 20, 0 };

		ImGui::Dummy({ 0, 10 });

		ImVec2 cursorPos = ImGui::GetCursorScreenPos();
		cursorPos.x += 10;
		ImVec2 contentMax = ImGui::GetContentRegionAvail();
		contentMax.x -= 20;

		Controls::DrawRect(cursorPos, contentMax, 76, Color(255, 255, 255, 10), 6.0f);

		cursorPos.x += 8;
		cursorPos.y += 3;
		float imageSize = 70.0f;
		Controls::DrawImageRounded((ImTextureID)component.Texture->GetID(), cursorPos, { cursorPos.x + imageSize, cursorPos.y + imageSize }, { 0, 1 }, { 1, 0 }, 4.0f);

		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 120);
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 25);
		ImGui::PushFont(editorFonts->SemiBold);
		ImGui::Text(component.Texture->GetPath().c_str());
		ImGui::PopFont();

		ImGui::Dummy({ 0, 50 });

		float availWidth = ImGui::GetContentRegionMax().x;

		if (availWidth > 500)
		{
			ImGui::SetNextItemWidth(availWidth * 0.3f);
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (availWidth * 0.7f) * 0.5f);
		}
		else if (availWidth > 340)
		{
			ImGui::SetNextItemWidth(availWidth * 0.5f);
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (availWidth * 0.5f) * 0.5f);
		}
		else
		{
			ImGui::SetNextItemWidth(availWidth - 30.0f);
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 15.0f);
		}

		ImGui::ColorPicker4("Preview", component.Tint, ImGuiColorEditFlags_NoSmallPreview | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoLabel);

		ImGui::Dummy({ 0, 15 });

		Controls::DrawVector2("Tiling", component.Tiling, offset, 1.0f);

		ImGui::Dummy({ 0, 15 });
	});

	DrawComponent<LuaScriptComponent>(ICON_TH " Lua Script Component", entity, m_LuaScriptOpened, m_LuaScriptPrimaryColor, 70.0f, p_EditorFonts, [](auto& component, EditorFonts* editorFonts)
	{
		ImVec2 offset = { 20, 0 };
		ImGui::Dummy({ 0, 5 });
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 20);
		ImGui::Text(component.Source.c_str());
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("LUA_SCRIPT_SOURCE"))
			{
				const char* scriptSrc = (const char*)payload->Data;
				component.Source = std::string(scriptSrc);
			}

			ImGui::EndDragDropTarget();
		}
		ImGui::Dummy({ 0, 15 });
	});

	ImGui::PopFont();
}