#include "Editor/Panels/Scene/SceneHierarchyPanel.h"

#include "Editor/CobaltEditor.h"

SceneHierarchyPanel* SceneHierarchyPanel::s_Instance = nullptr;

SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& scene) : EditorPanel("Scene hierarchy panel"), m_Scene(scene)
{
	LOG_TRACE("{0} created!", m_PanelName);

	s_Instance = this;

	m_Texture = Texture::Create("assets\\textures\\uv_grid.png"); // TODO: Move custom textures to asset manager

	m_HoveredColor = ImColor(27, 48, 69);
	m_SelectedColor = ImColor(38, 74, 99);
	m_EvenNodeColor = ImColor(0, 0, 0, 40);
	m_OddNodeColor = ImColor(0, 0, 0, 80);
}

void SceneHierarchyPanel::Update()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 10));
	ImGui::Begin("Hierarchy");

	int node_index = 0;
	m_Scene->Reg().each([&](auto entityID)
	{
		Entity entity{ entityID, m_Scene.get() };
		DrawEntityNode(entity, node_index);

		node_index++;
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
			entity.AddComponent<SpriteRendererComponent>(m_Texture, glm::vec4(1.0), glm::vec2(1.0));
		}

		ImGui::EndPopup();
	}

	if (Input::GetKeyDown(KEYCODE_F2) && m_SelectedEntity)
		ImGui::OpenPopup("Rename");

	DrawRenamePopup(m_SelectedEntity);

	ImGui::End();
	ImGui::PopStyleVar();
}

void SceneHierarchyPanel::DrawEntityNode(Entity entity, int node_index)
{
	auto& tag = entity.GetComponent<TagComponent>();

	ImVec2 cursor_pos = ImGui::GetCursorScreenPos();
	ImVec2 content_region_max = ImGui::GetContentRegionMax();

	float line_height = ImGui::GetTextLineHeight();

	if (node_index & 1)
		AddRectToDrawList(cursor_pos, content_region_max, line_height, m_EvenNodeColor);
	else
		AddRectToDrawList(cursor_pos, content_region_max, line_height, m_OddNodeColor);

	ImVec2 mouse_pos = ImGui::GetMousePos();
	if (mouse_pos.x > cursor_pos.x && mouse_pos.x < cursor_pos.x + content_region_max.x && mouse_pos.y > cursor_pos.y - 4.5f && mouse_pos.y < cursor_pos.y + line_height + 9)
	{
		AddRectToDrawList(cursor_pos, content_region_max, line_height, m_HoveredColor);

		if (ImGui::IsMouseClicked(0))
			m_SelectedEntity = entity;

		if (ImGui::IsMouseDoubleClicked(0) && m_SelectedEntity == entity)
		{
			ImGui::OpenPopup("Rename");
		}
	}
	else if(ImGui::IsMouseClicked(0) && m_SelectedEntity == entity && ImGui::IsWindowHovered())
		m_SelectedEntity = {};


	auto editor_font = CobaltEditor::GetEditorLayer()->GetEditorFonts();
	if (m_SelectedEntity == entity)
	{
		AddRectToDrawList(cursor_pos, content_region_max, line_height, m_SelectedColor);
		ImGui::PushFont(editor_font.SemiBold);
	}
	else
	{
		ImGui::PushFont(editor_font.Regular);
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
		
		ImGui::PushFont(CobaltEditor::GetEditorLayer()->GetEditorFonts().SemiBold);
		ImGui::Text("Raname");
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

void SceneHierarchyPanel::AddRectToDrawList(ImVec2 cursor_pos, ImVec2 content_region, float height, ImU32 color)
{
	auto* draw_list = ImGui::GetWindowDrawList();
	ImVec2 pos = ImVec2(cursor_pos.x, cursor_pos.y - 6);
	draw_list->AddRectFilled(pos, ImVec2(pos.x + content_region.x, pos.y + height + 12), color);
}
