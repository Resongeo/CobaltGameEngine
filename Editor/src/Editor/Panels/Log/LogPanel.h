#pragma once

#include "Editor/Panels/EditorPanel.h"
#include "Editor/Panels/Log/Logs.h"

#include "Cobalt.h"
using namespace Cobalt;

class LogPanel : public EditorPanel
{
public:
	LogPanel();
	virtual void Update() override;

private:
	bool m_ScrollToBottom = true;
	ImU32 m_OddColor;
	ImU32 m_EvenColor;
};
