#include "Editor/Panels/Profiler/RenderStatisticsPanel.h"
#include "Editor/CobaltEditor.h"

RenderStatisticsPanel::RenderStatisticsPanel() : EditorPanel("Renderer Statistics") { }

void RenderStatisticsPanel::Update()
{
	auto editorFonts = CobaltEditor::GetEditorLayer()->GetEditorFonts();
	auto& stats = RenderCommand::GetStats();

	ImGui::Begin("Render Statistics");

	ImGui::Columns(2);

	ImGui::PushFont(editorFonts.SemiBold);
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