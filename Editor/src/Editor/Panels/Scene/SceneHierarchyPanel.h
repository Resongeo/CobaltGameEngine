#pragma once

#include "Cobalt.h"
using namespace Cobalt;

#include "Editor/Panels/EditorPanel.h"
#include "Editor/Panels/Log/LogPanel.h"

class SceneHierarchyPanel : public EditorPanel
{
public:
	SceneHierarchyPanel(const Ref<Scene>& scene);

	void SetScene(const Ref<Scene>& scene) { m_Scene = scene; }
	virtual void ImGuiUpdate() override;

	static Entity GetSelectedEntity() { return s_Instance->m_SelectedEntity; }
	static void SetSelectedEntity(Entity entity) { s_Instance->m_SelectedEntity = entity; }
	static void DeselectEntity() { s_Instance->m_SelectedEntity = {}; }

private:
	void DrawEntityNode(Entity entity, int node_index);
	void DrawRenamePopup(Entity entity);

private:
	static SceneHierarchyPanel* s_Instance;

	Ref<Scene> m_Scene;
	Entity m_SelectedEntity;

	Ref<Texture2D> m_Texture;

	Color m_HoveredColor;
	Color m_SelectedColor;
	Color m_EvenNodeColor;
	Color m_OddNodeColor;
};