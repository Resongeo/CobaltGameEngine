#include "Editor/Style/Icons.h"
#include "Editor/Panels/Log/LogPanel.h"

LogPanel* LogPanel::s_Instance = nullptr;
LogPanel::LogPanel() : EditorPanel("Log panel")
{
	s_Instance = this;
}

void LogPanel::Clear()
{
	m_Messages.clear();
}

void LogPanel::Update()
{
	ImGui::Begin(ICON_INFO_CIRCLE " Log");

	if (ImGui::Button(ICON_TIMES_CIRCLE " Clear")) Clear();
	ImGui::SameLine();
	ImGui::Checkbox("Auto scroll", &m_ScrollToBottom);

	ImGui::Separator();

	ImGui::BeginChild("scroll", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

	for (auto& message : m_Messages)
	{
		ImGui::TextColored(message.Color, ICON_EXCLAMATION_TRIANGLE);
		ImGui::SameLine();
		ImGui::TextColored(message.Color, message.Message.c_str());
		if (m_ScrollToBottom && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
			ImGui::SetScrollHereY(1.0f);
		ImGui::Separator();
	}
	
	ImGui::EndChild();

	ImGui::End();
}