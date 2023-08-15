#pragma once

#include "Cobalt.h"
using namespace Cobalt;

#include "Editor/Panels/EditorPanel.h"

class ComponentsPanel : public EditorPanel
{
public:
	ComponentsPanel();

	void Update() override;
	void ImGuiUpdate() override;

private:
	void DrawComponents(Entity entity);

private:
	Entity m_SelectedEntity = {};
	ImVec2 m_CursorPos;
	ImVec2 m_ContentMax;

	Color m_TagPrimaryColor = Color(99, 167, 224, 255);
	Color m_TransformPrimaryColor = Color(222, 157, 95, 255);
	Color m_SpritePrimaryColor = Color(224, 162, 223, 255);
	Color m_LuaScriptPrimaryColor = Color(93, 217, 124, 255);

	bool m_TagOpened = true;
	bool m_TransformOpened = true;
	bool m_SpriteOpened = true;
	bool m_LuaScriptOpened = true;
};