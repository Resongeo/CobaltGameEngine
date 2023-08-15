#pragma once

#include <vector>

class EditorPanel;

class EditorPanelManager
{
public:
	static void Init();
	static void Update();
	static void ImGuiUpdate();

	static std::vector<EditorPanel*> GetPanels() { return s_Instance->m_Panels; }

private:
	static void PushPanel(EditorPanel* panel);
	friend class EditorPanel;

private:
	static EditorPanelManager* s_Instance;
	std::vector<EditorPanel*> m_Panels;
};