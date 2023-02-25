#pragma once

#include "Editor/Panels/EditorPanelSystem.h"
#include <string>

class EditorPanel
{
public:
	EditorPanel(const char* panelName) : m_PanelName(panelName)
	{
		EditorPanelSystem::PushPanel(this);
	}

	virtual void Update() = 0;

	const char* GetName() const { return m_PanelName; }

protected:
	const char* m_PanelName;
};