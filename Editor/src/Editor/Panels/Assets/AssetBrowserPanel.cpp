#include "Editor/Panels/Assets/AssetBrowserPanel.h"
#include "Editor/Panels/Log/LogPanel.h"

#include "Editor/Utils/Colors.h"

#include <filesystem>

AssetBrowserPanel::AssetBrowserPanel(const Ref<Scene>& scene) : m_Scene(scene), EditorPanel("Asset Browser")
{
	m_AssetDir = "..\\assets"; // TODO: Get this path from args
	m_CurrentDir = m_AssetDir;

	m_DirectoryIcon = Texture2D::Create("..\\assets\\icons\\asset_browser\\directory.png");
	m_FontIcon = Texture2D::Create("..\\assets\\icons\\asset_browser\\font.png");
	m_SceneIcon = Texture2D::Create("..\\assets\\icons\\asset_browser\\scene.png");
	m_ScriptIcon = Texture2D::Create("..\\assets\\icons\\asset_browser\\script.png");
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

	static float padding = 12.0f;
	static float thumbnailSize = 110.0f;
	float cellSize = thumbnailSize + padding;
	float panelWidth = ImGui::GetContentRegionAvail().x;
	int columnCount = (int)(panelWidth / cellSize);
	if (columnCount < 1) columnCount = 1;

	ImGui::Columns(columnCount, 0, false);

	for (auto& file : std::filesystem::directory_iterator(m_CurrentDir))
	{
		std::string path = file.path().string();

		ImGui::PushID(path.c_str());

		ImGui::PushStyleColor(ImGuiCol_Button, { 0, 0, 0, 0 });
		if (file.is_directory())
		{
			Vec3 dirColor = Colors::RGBtoVec3(232, 183, 60);
			const char* dirPath = path.c_str();

			if (m_DirectoryColors.find(path) == m_DirectoryColors.end())
				m_DirectoryColors[path] = dirColor;
			else
				dirColor = m_DirectoryColors[path];

			if (ImGui::ImageButton((ImTextureID)m_DirectoryIcon->GetID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 }, -1, { 0, 0, 0, 0 }, { dirColor.x, dirColor.y, dirColor.z, 1.0 }))
			{
				m_CurrentDir /= file.path().filename();
			}

			if (ImGui::IsItemClicked(1))
			{
				ImGui::OpenPopup("DIRECTORY_EDIT_POPUP");
			}

			if (ImGui::BeginPopup("DIRECTORY_EDIT_POPUP"))
			{
				ImGui::Text(dirPath);
				ImGui::ColorEdit3("##dircol", glm::value_ptr(m_DirectoryColors[path]));
				ImGui::EndPopup();
			}

			ImGui::TextWrapped(file.path().filename().string().c_str());
		}
		else
		{
			Ref<Texture2D> icon;
			auto extension = file.path().extension();

			if (extension == ".ttf")
				icon = m_FontIcon;
			else if (extension == ".cbscene")
				icon = m_SceneIcon;
			else if (extension == ".lua")
				icon = m_ScriptIcon;
			else
				icon = Texture2D::Create(1, 1);

			if (ImGui::ImageButton((ImTextureID)icon->GetID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 }))
			{
				if (extension == ".cbscene")
				{
					SceneHierarchyPanel::DeselectEntity();

					SceneSerializer serializer;
					serializer.Deserialize(path.c_str(), m_Scene);
				}
			}

			if (extension == ".lua")
			{
				if (ImGui::BeginDragDropSource())
				{
					std::string scriptSrc = file.path().string();
					ImGui::SetDragDropPayload("LUA_SCRIPT_SOURCE", scriptSrc.c_str(), (scriptSrc.size() + 1) * sizeof(char), ImGuiCond_Once);
					ImGui::EndDragDropSource();
				}
			}

			ImGui::TextWrapped(file.path().filename().string().c_str());
		}
		ImGui::PopStyleColor();
		
		ImGui::NextColumn();
		ImGui::PopID();
	}

	ImGui::Columns(1);
	ImGui::End();
}
