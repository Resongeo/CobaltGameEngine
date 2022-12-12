#pragma once

#include "Cobalt.h"
using namespace Cobalt;

#include "Editor/Panels/EditorPanel.h"
#include "Editor/Panels/Log/LogPanel.h"

class SceneHierarchyPanel : public EditorPanel
{
public:
	SceneHierarchyPanel(const Ref<Scene>& scene);

	inline void SetScene(const Ref<Scene>& scene) { m_Scene = scene; }

	void Update() override;

private:
	void DrawEntityNode(Entity entity, int node_index);
	void AddRectToDrawList(ImVec2 cursor_pos, ImVec2 content_region, float line_height, ImU32 color);

private:
	Ref<Scene> m_Scene;
	Entity m_SelectedEntity;

	ImU32 m_HoveredColor;
	ImU32 m_SelectedColor;
	ImU32 m_EvenNodeColor;
	ImU32 m_OddNodeColor;
};