#include "Editor/Style/Icons.h"
#include "Editor/Panels/Log/LogPanel.h"

#include "Editor/Utils/Controls.h"
#include "Editor/Utils/Colors.h"

LogPanel::LogPanel() : EditorPanel("Log panel")
{
	m_OddColor = ImColor(0, 0, 0, 20);
	m_EvenColor = ImColor(0, 0, 0, 40);
}

void LogPanel::Update()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 10));
	ImGui::Begin(ICON_INFO_CIRCLE " Log");

	ImGui::SetCursorPosX(10);
	ImGui::PushStyleColor(ImGuiCol_Button, Colors::RGBAtoImVec4(60, 100, 140));
	if (ImGui::Button(ICON_TIMES_CIRCLE " Clear")) Logs::Get().Clear();
	ImGui::PopStyleColor();
	ImGui::SameLine();
	ImGui::Checkbox("Auto scroll", &m_ScrollToBottom);

	ImGui::BeginChild("scroll", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
	ImGui::Dummy(ImVec2(0, 5));

	int logIndex = 0;
	for (auto& message : Logs::Get().GetMessages())
	{
		Controls::DrawRect(ImGui::GetCursorScreenPos(), ImGui::GetContentRegionMax(), ImGui::GetTextLineHeight(), logIndex & 1 ? m_OddColor : m_EvenColor);

		ImGui::SetCursorPosX(8);
		ImGui::TextColored(message.Color, ICON_EXCLAMATION_TRIANGLE);
		ImGui::SameLine();
		ImGui::TextColored(message.Color, message.Message.c_str());

		if (m_ScrollToBottom && ImGui::GetScrollY() >= ImGui::GetScrollMaxY() - 10.0)
			ImGui::SetScrollHereY(1.0f);

		ImGui::Dummy(ImVec2(0, 4));

		logIndex++;
	}
	
	ImGui::EndChild();

	ImGui::End();
	ImGui::PopStyleVar();
}