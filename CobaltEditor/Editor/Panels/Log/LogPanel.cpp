#include "Editor/Panels/Log/LogPanel.h"

LogPanel* LogPanel::s_Instance = nullptr;

LogPanel::LogPanel() : EditorPanel("Log panel")
{
	s_Instance = this;

	LOG_TRACE("{0} created!", m_PanelName);

	DEBUG_LOG("Debug Log message!");
	DEBUG_INFO("Debug Info message!");
	DEBUG_WARN("Debug Warn message!");
	DEBUG_ERROR("Debug Error message!");
}

void LogPanel::Clear()
{
	m_Messages.clear();
}

void LogPanel::Update()
{
	ImGui::Begin("Log");

	if (ImGui::Button("Clear")) Clear();
	ImGui::SameLine();
	ImGui::Checkbox("Auto scroll", &m_ScrollToBottom);

	ImGui::Separator();

	ImGui::BeginChild("scroll", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

	for (auto& message : m_Messages)
	{
		ImGui::TextColored(message.Color, message.Message.c_str());
		if (m_ScrollToBottom && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
			ImGui::SetScrollHereY(1.0f);
		ImGui::Separator();
	}
	
	ImGui::EndChild();

	ImGui::End();
}