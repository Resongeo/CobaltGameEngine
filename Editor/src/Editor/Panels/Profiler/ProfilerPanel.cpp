#include "Editor/Panels/Profiler/ProfilerPanel.h"

ProfilerPanel* ProfilerPanel::s_Instance = nullptr;
ProfilerPanel::ProfilerPanel() : EditorPanel("Profiler panel")
{
	s_Instance = this;
	m_ActiveHeader = nullptr;
}

void ProfilerPanel::Update()
{
	ImGui::Begin(ICON_CLOCK " Profiler");

	for (auto& header : m_ProfilerHeaders)
	{
		auto windowWidth = ImGui::GetWindowSize().x;
		auto textWidth = ImGui::CalcTextSize(header.Name).x;
		ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);

		ImGui::PushFont(p_EditorFonts->SemiBold);
		ImGui::TextColored(ImVec4(0.176, 0.450, 0.705, 1.0), header.Name);
		ImGui::PopFont();

		for (auto& profile : header.Results)
		{
			ImGui::Text(profile.Name);
			ImGui::SameLine();

			std::string label = fmt::format("%.3f ms", profile.Duration);
			textWidth = ImGui::CalcTextSize(label.c_str()).x;
			ImGui::SetCursorPosX((windowWidth - textWidth) - 30);

			ImGui::Text("%.3f ms", profile.Duration);
		}
	}

	ImGui::End();

	m_ProfilerHeaders.clear();
}

void ProfilerPanel::AddProfilerResult(const char* name, float duration)
{
	m_ActiveHeader.Results.push_back(ProfilerResult(name, duration));
}

void ProfilerPanel::StartProfilerHeader(const char* name)
{
	m_ActiveHeader = ProfilerHeader(name);
}

void ProfilerPanel::StopProfilerHeader()
{
	m_ProfilerHeaders.push_back(m_ActiveHeader);
}