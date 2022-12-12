#include "Editor/Panels/Log/LogPanel.h"

LogPanel* LogPanel::s_Instance = nullptr;

LogPanel::LogPanel() : EditorPanel("Log panel")
{
	s_Instance = this;

	LOG_TRACE("Panel {0} created!", m_PanelName);

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

void LogPanel::AddLog(const std::string& message)
{
	m_Messages.push_back(LogMessage(message, ImVec4(0.94f, 0.94f, 0.94f, 1.0f)));
}

void LogPanel::AddInfo(const std::string& message)
{
	m_Messages.push_back(LogMessage(message, ImVec4(0.40f, 0.85f, 0.40f, 1.0f)));
}

void LogPanel::AddWarn(const std::string& message)
{
	m_Messages.push_back(LogMessage(message, ImVec4(0.85f, 0.85f, 0.21f, 1.0f)));
}

void LogPanel::AddError(const std::string& message)
{
	m_Messages.push_back(LogMessage(message, ImVec4(0.85f, 0.32f, 0.32f, 1.0f)));
}