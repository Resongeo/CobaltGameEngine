#pragma once

#include "CobaltEditor/Panels/EditorPanel.h"

namespace CobaltEditor
{
	class SceneHierarchyPanel : public EditorPanel
	{
	public:
		SceneHierarchyPanel(const Ref<Scene>& scene);

		void Update() override { }
		void UIRender() override;

		static void DeselectEntity() { s_Instance->m_SelectedEntity = {}; }
		static void SetSelectedEntity(Entity entity) { s_Instance->m_SelectedEntity = entity; }
		static Entity GetSelectedEntity() { return s_Instance->m_SelectedEntity; }

		static Ref<SceneHierarchyPanel> Create(const Ref<Scene>& scene);

	private:
		inline void DrawEntityNode(Entity entity);
		inline bool MouseOverNode(const ImVec2& min, const ImVec2& max);

	private:
		static SceneHierarchyPanel* s_Instance;

		Ref<Scene> m_Scene;
		Entity m_SelectedEntity = {};

		Color m_EvenColor = Color(30, 30, 30);
		Color m_OddColor = Color(35, 35, 35);
		Color m_HoverColor = Color(50, 50, 50);
		Color m_SelectColor = Color(50, 90, 140);
		Color m_SelectHoverColor = Color(90, 110, 140);
		Vec2 m_Padding = Vec2(15.0f, 9.0f);
		float m_BottomMargin = 1.9f;
		uint32_t m_NodeCounter = 0;
	};
}