#include "pch.h"
#include "CobaltEditor/Panels/SceneHierarchyPanel.h"

namespace CobaltEditor
{
	SceneHierarchyPanel* SceneHierarchyPanel::s_Instance = nullptr;

	SceneHierarchyPanel::SceneHierarchyPanel()
	{
		s_Instance = this;
	}

	void SceneHierarchyPanel::OnLoad()
	{
		auto& colors = StyleManager::GetColors();
		m_EvenColor = colors.Panels.SceneHierarchy.EvenColor;
		m_OddColor = colors.Panels.SceneHierarchy.OddColor;
		m_HoverColor = colors.Panels.SceneHierarchy.HoverColor;
		m_SelectColor = colors.Panels.SceneHierarchy.SelectColor;
		m_SelectHoverColor = colors.Panels.SceneHierarchy.SelectHoverColor;
	}

	void SceneHierarchyPanel::OnUpdate()
	{
		m_Scene = SceneManager::GetActiveScene();
	}

	void SceneHierarchyPanel::OnUIRender()
	{
		ScopedStyleVar _(ImGuiStyleVar_WindowPadding, { 0, 0 });

		ImGui::Begin("Scene Hierarchy");
		{
			m_NodeCounter = 0;
			m_Scene->Registry().each([&](auto entityID)
			{
				Entity entity{ entityID, m_Scene.get() };
				DrawEntityNode(entity);
				m_NodeCounter++;
			});
		}
		ImGui::End();
	}

	Ref<SceneHierarchyPanel> SceneHierarchyPanel::Create()
	{
		auto panel = CreateRef<SceneHierarchyPanel>();
		EditorPanelManager::PushPanel(panel);

		return panel;
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		ScopedID _(entity);

		std::string& tag = entity.GetComponent<TagComponent>().Tag;
		ImDrawList* drawList = ImGui::GetWindowDrawList();
		ImVec2 cursorPos = ImGui::GetCursorScreenPos();
		ImVec2 contentRegionMax = ImGui::GetContentRegionMax();
		float textLineHeight = ImGui::GetTextLineHeight();

		Color nodeBgColor;

		if (MouseOverNode(cursorPos, { cursorPos.x + contentRegionMax.x, cursorPos.y + textLineHeight + (m_Padding.y * 2) }))
		{
			if (Input::GetMouseButtonClicked(MOUSE_BUTTON_LEFT))
			{
				m_SelectedEntity = entity;
			}

			nodeBgColor = m_SelectedEntity == entity ? m_SelectHoverColor : m_HoverColor;
		}
		else
		{
			if (Input::GetMouseButtonClicked(MOUSE_BUTTON_LEFT) && m_SelectedEntity == entity && ImGui::IsWindowHovered())
			{
				m_SelectedEntity = {};
			}

			if (m_SelectedEntity == entity)
			{
				nodeBgColor = m_SelectColor;
			}
			else
			{
				nodeBgColor = m_NodeCounter & 1 ? m_OddColor : m_EvenColor;
			}
		}

		drawList->AddRectFilled(cursorPos, { cursorPos.x + contentRegionMax.x, cursorPos.y + textLineHeight + (m_Padding.y * 2)}, nodeBgColor);
		cursorPos = ImGui::GetCursorPos();
		ImGui::SetCursorPos({ cursorPos.x + m_Padding.x, cursorPos.y + m_Padding.y });
		ImGui::Text(tag.c_str());

		ImGui::Dummy({ 0, m_BottomMargin });
	}

	inline bool SceneHierarchyPanel::MouseOverNode(const ImVec2& min, const ImVec2& max)
	{
		auto mousePos = ImGui::GetMousePos();
		return mousePos.x > min.x && mousePos.x < max.x && mousePos.y > min.y && mousePos.y < max.y;
	}
}