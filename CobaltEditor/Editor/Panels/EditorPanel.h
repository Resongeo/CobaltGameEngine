#pragma once

#include <string>

class EditorPanel
{
public:
	EditorPanel(const std::string& panelName) : m_PanelName(panelName) {}
	virtual void Update(float deltaTime) = 0;

protected:
	std::string m_PanelName;
};