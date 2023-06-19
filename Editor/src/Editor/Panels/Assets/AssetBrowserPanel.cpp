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
					SceneHierarchyPanel::DeselectEntity();

					SceneSerializer serializer;
					serializer.Deserialize(path.c_str(), m_Scene);

					DEBUG_LOG("Scene loaded: {0}", file.path().stem().string());
				}
			}

			if (file.path().extension() == ".lua")
			{
				if (ImGui::BeginDragDropSource())
				{
					std::string scriptSrc = file.path().string();
					ImGui::SetDragDropPayload("LUA_SCRIPT_SOURCE", scriptSrc.c_str(), (scriptSrc.size() + 1) * sizeof(char), ImGuiCond_Once);
					ImGui::EndDragDropSource();
				}
			}

			ImGui::PopStyleColor();
		}
	}

	ImGui::End();
}
