#pragma once

#include "Editor/Panels/EditorPanel.h"

#include <filesystem>

class AssetBrowserPanel : public EditorPanel
{
public:
	AssetBrowserPanel();

	virtual void Update() override;

private:
	std::filesystem::path m_CurrentDir;
};