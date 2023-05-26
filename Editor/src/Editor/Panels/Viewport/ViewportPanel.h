#pragma once

#include "Cobalt.h"
using namespace Cobalt;

#include "Editor/Panels/EditorPanel.h"
#include "Editor/Panels/Scene/SceneHierarchyPanel.h"

class ViewportPanel : public EditorPanel
{
public:
	ViewportPanel(const Ref<Framebuffer>& framebuffer, EditorCamera* editorCamera, const Ref<Scene>& activeScene);

	virtual void Update() override;
	virtual void ImGuiUpdate() override;

	static bool IsGridShown() { return s_Instance->m_ShowGrid; }

private:
	static ViewportPanel* s_Instance;

	Ref<Framebuffer> m_Framebuffer;
	Ref<Scene> m_ActiveScene;

	EditorCamera* m_EditorCamera;
	ImVec2 m_ViewportSize;
	Vec2 m_ViewportBounds[2] = {};
	Entity m_SelectedEntity;

	ImGuizmo::OPERATION m_GizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
	ImGuizmo::MODE m_GizmoMode = ImGuizmo::MODE::LOCAL;

	int m_FBAttachmentID = 0;
	bool m_ShowFPS = true;
	bool m_ShowGrid = true;
};