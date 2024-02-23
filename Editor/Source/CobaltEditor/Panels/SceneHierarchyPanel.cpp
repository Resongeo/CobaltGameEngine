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

		m_ContextPopup.SetTitle("Create Entity");
		m_ContextPopup.AddMenuItem("Empty Entity", []()
		{
			SceneManager::GetActiveScene()->CreateEntity("Empty Entity");
		});
		m_ContextPopup.AddMenuItem("Square", []()
		{
			auto entity = SceneManager::GetActiveScene()->CreateEntity("Square");
			entity.AddComponent<SpriteRendererComponent>();
		});
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
		m_ContextPopup.Draw();
		ImGui::End();
	}

	Shared<SceneHierarchyPanel> SceneHierarchyPanel::Create()
	{
		auto panel = CreateShared<SceneHierarchyPanel>();
		EditorPanelManager::PushPanel(panel);

		return panel;
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		ScopedID _(entity);

		std::string& tag = entity.GetComponent<TagComponent>().Name;
		ImVec2 cursorPos = ImGui::GetCursorScreenPos();
		ImVec2 contentRegionMax = ImGui::GetContentRegionMax();
		float textLineHeight = ImGui::GetTextLineHeight();

		Color nodeBgColor;

		if (MouseUtils::Intersect(cursorPos, { cursorPos.x + contentRegionMax.x, cursorPos.y + textLineHeight + (m_Padding.y * 2) }))
		{
			if (Input::GetMouseButtonClicked(MOUSE_BUTTON_LEFT))
			{
				m_SelectedEntity = entity;
			}

			nodeBgColor = m_SelectedEntity == entity ? m_SelectHoverColor : m_HoverColor;
		}
		else
		{
			if (Input::GetMouseButtonClicked(MOUSE_BUTTON_LEFT) && ImGui::IsWindowHovered())
			{
				if (m_SelectedEntity == entity)
				{
					m_SelectedEntity = {};
				}

				m_ContextPopup.Close();
			}

			if (Input::GetMouseButtonClicked(MOUSE_BUTTON_RIGHT) && ImGui::IsWindowHovered())
			{
				m_ContextPopup.Open();
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

		Shapes::DrawRect(cursorPos, { cursorPos.x + contentRegionMax.x, cursorPos.y + textLineHeight + (m_Padding.y * 2)}, nodeBgColor);
		
		cursorPos = ImGui::GetCursorPos();
		ImGui::SetCursorPos({ cursorPos.x + m_Padding.x, cursorPos.y + m_Padding.y });
		ImGui::Text(tag.c_str());

		ImGui::Dummy({ 0, m_BottomMargin });
	}
}