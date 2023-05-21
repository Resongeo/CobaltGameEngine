#include "Editor/Panels/Assets/AssetBrowserPanel.h"
#include "Editor/Panels/Log/LogPanel.h"

#include <filesystem>

AssetBrowserPanel::AssetBrowserPanel(const Ref<Scene>& scene) : m_Scene(scene), EditorPanel("Asset Browser")
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
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.8, 0.5, 0.5, 1.0));
			if (ImGui::Button(file.path().stem().string().c_str()))
			{
				if (file.path().extension() == ".cbscene")
				{
					SceneSerializer serializer;
					serializer.Deserialize(path.c_str(), m_Scene);

					DEBUG_LOG("Scene loaded: {0}", file.path().stem().string());
				}
			}
			ImGui::PopStyleColor();
		}
	}

	ImGui::End();
}
