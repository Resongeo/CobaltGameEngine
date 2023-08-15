#pragma once

#include "Editor/Panels/EditorPanel.h"
#include "Editor/Panels/Log/Logs.h"

#include "Cobalt.h"
using namespace Cobalt;

class LogPanel : public EditorPanel
{
public:
	LogPanel();
	virtual void ImGuiUpdate() override;

private:
	bool m_ScrollToBottom = true;
	Color m_OddColor;
	Color m_EvenColor;
};
