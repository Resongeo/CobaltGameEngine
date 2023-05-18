#pragma once

#include "Cobalt.h"
using namespace Cobalt;
#include "Editor/Panels/EditorPanel.h"

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
};