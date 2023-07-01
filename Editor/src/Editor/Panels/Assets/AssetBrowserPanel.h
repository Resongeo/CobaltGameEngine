#pragma once

#include "Cobalt.h"
using namespace Cobalt;

#include "Editor/Panels/EditorPanel.h"
#include "Editor/Panels/Scene/SceneHierarchyPanel.h"

#include <filesystem>

class AssetBrowserPanel : public EditorPanel
{
public:
	AssetBrowserPanel(const Ref<Scene>& scene);

	virtual void Update() override;

private:
	std::filesystem::path m_CurrentDir;
	const char* m_AssetDir;

	Ref<Scene> m_Scene;

	Ref<Texture2D> m_DirectoryIcon;
	Ref<Texture2D> m_FontIcon;
	Ref<Texture2D> m_SceneIcon;
	Ref<Texture2D> m_ScriptIcon;

	std::unordered_map<std::string, Vec3> m_DirectoryColors;
};