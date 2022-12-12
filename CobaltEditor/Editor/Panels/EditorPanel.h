#pragma once

#include <string>

class EditorPanel
{
public:
	EditorPanel(const std::string& panelName) : m_PanelName(panelName) {}
	virtual void Update() = 0;

protected:
	std::string m_PanelName;
};