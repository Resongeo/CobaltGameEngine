#pragma once

#include "CobaltEditor/Components/ContextPopup.h"
#include "CobaltEditor/Panels/EditorPanel.h"

namespace CobaltEditor
{
	class SceneHierarchyPanel : public EditorPanel
	{
	public:
		SceneHierarchyPanel();

		void OnLoad() override;
		void OnUpdate() override;
		void OnUIRender() override;

		static void DeselectEntity() { s_Instance->m_SelectedEntity = {}; }
		static void SetSelectedEntity(Entity entity) { s_Instance->m_SelectedEntity = entity; }
		static Entity GetSelectedEntity() { return s_Instance->m_SelectedEntity; }

		static Shared<SceneHierarchyPanel> Create();

	private:
		inline void DrawEntityNode(Entity entity);

	private:
		static SceneHierarchyPanel* s_Instance;

		Shared<Scene> m_Scene;
		Entity m_SelectedEntity = {};

		Color m_EvenColor;
		Color m_OddColor;
		Color m_HoverColor;
		Color m_SelectColor;
		Color m_SelectHoverColor;
		Vec2 m_Padding = Vec2(15.0f, 9.0f);
		float m_BottomMargin = 1.9f;
		u32 m_NodeCounter = 0;

		ContextPopup m_ContextPopup;
	};
}