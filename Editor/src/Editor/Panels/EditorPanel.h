#pragma once

#include "Editor/Panels/EditorPanelManager.h"
#include "Editor/Style/StyleManager.h"
#include "Editor/Style/Icons.h"

#include <string>

class EditorPanel
{
public:
	EditorPanel() = default;
	EditorPanel(const char* panelName) : m_PanelName(panelName)
	{
		EditorPanelManager::PushPanel(this);
		p_EditorFonts = StyleManager::GetEditorFonts();
	}

	virtual void Update() { }
	virtual void ImGuiUpdate() { }

	const char* GetName() const { return m_PanelName; }

protected:
	const char* m_PanelName = "Panel";
	EditorFonts* p_EditorFonts = nullptr;
};