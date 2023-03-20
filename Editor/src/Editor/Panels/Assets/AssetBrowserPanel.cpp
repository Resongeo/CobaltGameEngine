#include "Editor/Panels/Assets/AssetBrowserPanel.h"

#include <filesystem>

AssetBrowserPanel::AssetBrowserPanel() : EditorPanel("Asset Browser")
{
	m_CurrentDir = "assets";
}

void AssetBrowserPanel::Update()
{
	ImGui::Begin("Asset Browser");

	if (m_CurrentDir != "assets")
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
