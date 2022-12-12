#include "Editor/Panels/Profiler/ProfilerPanel.h"
#include "Editor/CobaltEditor.h"

ProfilerPanel* ProfilerPanel::s_Instance = nullptr;

Timer::Timer(const char* name) : m_Name(name)
{
	m_StartTime = std::chrono::high_resolution_clock::now();
}

Timer::~Timer()
{
	auto endTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - m_StartTime).count() * 0.001f;

	ProfilerPanel::Get().AddProfilerResult(m_Name, duration);
}

ProfilerPanel::ProfilerPanel() : EditorPanel("Profiler panel")
{
	s_Instance = this;
	m_ActiveHeader = nullptr;
}

void ProfilerPanel::Update()
{
	ImGui::Begin("Profiler");

	for (auto& header : m_ProfilerHeaders)
	{
		auto windowWidth = ImGui::GetWindowSize().x;
		auto textWidth = ImGui::CalcTextSize(header.Name).x;
		ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);

		ImGui::PushFont(CobaltEditor::GetEditorLayer()->GetEditorFonts().SemiBold);
		ImGui::TextColored(ImVec4(0.176, 0.450, 0.705, 1.0), header.Name);
		ImGui::PopFont();

		for (auto& profile : header.Results)
		{
			ImGui::Text(profile.Name);
			ImGui::SameLine();

			std::string label = fmt::format("%.3f ms", profile.Duration);
			textWidth = ImGui::CalcTextSize(label.c_str()).x;
			ImGui::SetCursorPosX((windowWidth - textWidth) - 20);

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
	m_ActiveHeader = nullptr;
}