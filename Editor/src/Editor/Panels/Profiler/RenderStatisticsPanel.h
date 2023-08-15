#pragma once

#include "Cobalt.h"
using namespace Cobalt;

#include "Editor/Panels/EditorPanel.h"

class RenderStatisticsPanel : public EditorPanel
{
public:
	RenderStatisticsPanel();
	void ImGuiUpdate() override;
};