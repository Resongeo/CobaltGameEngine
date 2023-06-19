#pragma once

#include "Cobalt.h"
using namespace Cobalt;

#include "Editor/Panels/EditorPanel.h"

class ComponentsPanel : public EditorPanel
{
public:
	ComponentsPanel();

	virtual void Update() override;
	virtual void ImGuiUpdate() override;

private:
	void DrawComponents(Entity entity);

private:
	Entity m_SelectedEntity = {};
	ImVec2 m_CursorPos;
	ImVec2 m_ContentMax;

	Vec4 m_TagPrimaryColor { 99, 167, 224, 255 };
	Vec4 m_TransformPrimaryColor { 222, 157, 95, 255 };
	Vec4 m_SpritePrimaryColor { 224, 162, 223, 255 };
	Vec4 m_LuaScriptPrimaryColor { 93, 217, 124, 255 };

	bool m_TagOpened = true;
	bool m_TransformOpened = true;
	bool m_SpriteOpened = true;
	bool m_LuaScriptOpened = true;
};