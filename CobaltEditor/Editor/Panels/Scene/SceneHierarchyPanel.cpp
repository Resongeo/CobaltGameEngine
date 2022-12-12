#include "Editor/Panels/Scene/SceneHierarchyPanel.h"

#include "Editor/CobaltEditor.h"

SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& scene) : EditorPanel("Scene hierarchy panel"), m_Scene(scene)
{
	LOG_TRACE("Panel {0} created!", m_PanelName);

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
	{
		AddRectToDrawList(cursor_pos, content_region_max, line_height, m_EvenNodeColor);
	}
	else
	{
		AddRectToDrawList(cursor_pos, content_region_max, line_height, m_OddNodeColor);
	}

	ImVec2 mouse_pos = ImGui::GetMousePos();
	if (mouse_pos.x > cursor_pos.x && mouse_pos.x < cursor_pos.x + content_region_max.x && mouse_pos.y > cursor_pos.y - 4.5f && mouse_pos.y < cursor_pos.y + line_height + 9)
	{
		AddRectToDrawList(cursor_pos, content_region_max, line_height, m_HoveredColor);

		if (ImGui::IsMouseClicked(0))
		{
			m_SelectedEntity = entity;
		}
	}

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

void SceneHierarchyPanel::AddRectToDrawList(ImVec2 cursor_pos, ImVec2 content_region, float line_height, ImU32 color)
{
	auto* draw_list = ImGui::GetWindowDrawList();
	ImVec2 pos = ImVec2(cursor_pos.x, cursor_pos.y - 6);
	draw_list->AddRectFilled(pos, ImVec2(pos.x + content_region.x, pos.y + line_height + 12), color);
}
