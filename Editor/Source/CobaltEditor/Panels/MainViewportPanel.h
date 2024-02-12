#pragma once

#include "CobaltEditor/Panels/EditorPanel.h"
#include "CobaltEditor/Components/Viewport.h"

namespace CobaltEditor
{
	class MainViewportPanel : public EditorPanel
	{
	public:
		MainViewportPanel();

		void OnUpdate() override;
		void OnUIRender() override;
		void OnEvent(Event& event) override;

		static Shared<MainViewportPanel> Create();

	private:
		inline void ResizeViewport();
		inline void UpdateBounds();
		inline void DrawGizmo();
		inline void MousePick();
		inline void DrawGrid();

	private:
		Shared<Scene> m_Scene;
		Shared<Viewport> m_Viewport;
		Shared<EditorCamera> m_EditorCamera;

		Vec2 m_ViewportBounds[2] = {};
		ImVec2 m_ViewportOffset;
		ImVec2 m_ViewportSize;

		Entity m_SelectedEntity;

		ImGuizmo::OPERATION m_GizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
		ImGuizmo::MODE m_GizmoMode = ImGuizmo::MODE::LOCAL;
	};
}