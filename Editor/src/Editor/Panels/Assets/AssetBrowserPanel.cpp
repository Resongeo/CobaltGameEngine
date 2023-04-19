#include "Editor/Panels/Assets/AssetBrowserPanel.h"

#include <filesystem>

AssetBrowserPanel::AssetBrowserPanel() : EditorPanel("Asset Browser")
{
	m_AssetDir = "..\\assets"; // TODO: Get this path from args
	m_CurrentDir = m_AssetDir;
}

void AssetBrowserPanel::Update()
{
	ImGui::Begin("Asset Browser");

	ImGui::PushFont(p_EditorFonts->SemiBold);
	ImGui::TextColored(ImVec4(0.8, 0.5, 0.5, 1.0), "%s", "This panel has no functionality yet!");
	ImGui::PopFont();

	if (m_CurrentDir != m_AssetDir)
	{
		if (ImGui::Button("<--"))
		{
			m_CurrentDir = m_CurrentDir.parent_path();
		}
	}

	for (auto& file : std::filesystem::directory_iterator(m_CurrentDir))
	{
		std::string path = file.path().string();

		if (file.is_directory())
		{
			if (ImGui::Button(file.path().filename().string().c_str()))
			{
				m_CurrentDir /= file.path().filename();
			}
		}
		else
		{
			ImGui::TextColored(ImVec4(0.8, 0.5, 0.5, 1.0), "%s", path.c_str());
		}
	}

	ImGui::End();
}
