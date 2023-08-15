#include "Editor/Panels/Scene/SceneHierarchyPanel.h"
#include "Editor/Utils/Controls.h"

SceneHierarchyPanel* SceneHierarchyPanel::s_Instance = nullptr;
SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& scene) : EditorPanel(ICON_LIST_UL " Hierarchy"), m_Scene(scene)
{
	s_Instance = this;

	m_Texture = Texture2D::Create("..\\assets\\textures\\uv_grid.png"); // TODO: Move custom textures to asset manager

	m_HoveredColor = Color(27, 48, 69);
	m_SelectedColor = Color(38, 74, 99);
	m_EvenNodeColor = Color(0, 0, 0, 40);
	m_OddNodeColor = Color(0, 0, 0, 80);
}

void SceneHierarchyPanel::ImGuiUpdate()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 10));
	ImGui::Begin(GetName());

	int nodeIndex = 0;
	m_Scene->Registry().each([&](auto entityID)
	{
		Entity entity{ entityID, m_Scene.get() };
		DrawEntityNode(entity, nodeIndex);

		nodeIndex++;
	});

	if (ImGui::BeginPopupContextWindow())
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 10, 10 });
		ImGui::Text("Create new entity");
		ImGui::PopStyleVar();

		if (ImGui::MenuItem("Empty entity"))
			m_Scene->CreateEntity("Entity");

		if (ImGui::MenuItem("Empty Sprite"))
		{
			auto entity = m_Scene->CreateEntity("Sprite");
			entity.AddComponent<SpriteRendererComponent>();
		}

		if (ImGui::MenuItem("UV grid"))
		{
			auto entity = m_Scene->CreateEntity("UV grid");
			entity.AddComponent<SpriteRendererComponent>(m_Texture);
		}

		ImGui::EndPopup();
	}

	if (Input::GetKeyDown(KEYCODE_F2) && m_SelectedEntity)
		ImGui::OpenPopup("Rename");

	if (Input::GetKeyDown(KEYCODE_DELETE) && m_SelectedEntity)
	{
		m_Scene->DestroyEntity(m_SelectedEntity);
		m_SelectedEntity = {};
	}

	DrawRenamePopup(m_SelectedEntity);

	ImGui::End();
	ImGui::PopStyleVar();
}

void SceneHierarchyPanel::DrawEntityNode(Entity entity, int node_index)
{
	auto& tag = entity.GetComponent<TagComponent>();

	ImVec2 cursorPos = ImGui::GetCursorScreenPos();
	ImVec2 contentRegionMax = ImGui::GetContentRegionMax();

	float lineHeight = ImGui::GetTextLineHeight();

	Controls::DrawRect(cursorPos, contentRegionMax, lineHeight, node_index & 1 ? m_EvenNodeColor : m_OddNodeColor);

	ImVec2 mouse_pos = ImGui::GetMousePos();
	if (mouse_pos.x > cursorPos.x && mouse_pos.x < cursorPos.x + contentRegionMax.x && mouse_pos.y > cursorPos.y - 4.5f && mouse_pos.y < cursorPos.y + lineHeight + 9)
	{
		Controls::DrawRect(cursorPos, contentRegionMax, lineHeight, m_HoveredColor);

		if (ImGui::IsMouseClicked(0))
			m_SelectedEntity = entity;

		if (ImGui::IsMouseDoubleClicked(0) && m_SelectedEntity == entity)
			ImGui::OpenPopup("Rename");

	}
	else if (ImGui::IsMouseClicked(0) && m_SelectedEntity == entity && ImGui::IsWindowHovered())
	{
		m_SelectedEntity = {};
	}

	if (m_SelectedEntity == entity)
	{
		Controls::DrawRect(cursorPos, contentRegionMax, lineHeight, m_SelectedColor);
		ImGui::PushFont(p_EditorFonts->SemiBold);
	}
	else
	{
		ImGui::PushFont(p_EditorFonts->Regular);
	}

	ImGui::SetCursorPosX(10);
	ImGui::Text(tag);
	
	ImGui::Dummy(ImVec2(0, 4));

	ImGui::PopFont();
}


void SceneHierarchyPanel::DrawRenamePopup(Entity entity)
{
	if (ImGui::BeginPopup("Rename"))
	{
		auto windowWidth = ImGui::GetWindowSize().x;
		auto textWidth = ImGui::CalcTextSize("Rename").x;
		ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
		
		ImGui::PushFont(p_EditorFonts->SemiBold);
		ImGui::Text(ICON_TAG " Raname");
		ImGui::PopFont();

		ImGui::Text("New name");

		ImGui::SameLine();

		auto& tag = entity.GetComponent<TagComponent>();
		ImGui::InputText("##name", tag.Tag.data(), tag.Tag.capacity());

		if (Input::GetKeyDown(KEYCODE_ENTER) || Input::GetKeyDown(KEYCODE_ESCAPE))
			ImGui::CloseCurrentPopup();

		ImGui::EndPopup();
	}
}
