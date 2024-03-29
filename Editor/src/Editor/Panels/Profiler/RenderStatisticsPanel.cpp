#include "Editor/Panels/Profiler/RenderStatisticsPanel.h"

RenderStatisticsPanel::RenderStatisticsPanel() : EditorPanel(ICON_CHART_BAR " Render Statistics") { }

void RenderStatisticsPanel::ImGuiUpdate()
{
	auto& stats = RenderCommand::GetStats();

	ImGui::Begin(GetName());

	ImGui::Columns(2);

	ImGui::PushFont(p_EditorFonts->SemiBold);
	ImGui::Text("Draw calls:");
	ImGui::Text("Quad count:");
	ImGui::Text("Vertex count:");
	ImGui::Text("Index count:");
	ImGui::PopFont();

	ImGui::NextColumn();

	ImGui::Text("%d", stats.DrawCalls);
	ImGui::Text("%d", stats.QuadCount);
	ImGui::Text("%d", stats.GetVertexCount());
	ImGui::Text("%d", stats.GetIndexCount());

	ImGui::Columns(1);

	ImGui::End();
}