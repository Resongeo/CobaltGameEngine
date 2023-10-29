#include "CobaltEditor/Components/DockSpace.h"

namespace CobaltEditor
{
	float DockSpace::s_ToolbarHeight = 40.f; // TODO: Get this from a config

	void DockSpace::MasterSpace(const Ref<Cobalt::Window>& window)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		Vec2 windowPos = window->GetPosition();

		ImGui::SetNextWindowPos({ viewport->Pos.x, viewport->Pos.y + s_ToolbarHeight });
		ImGui::SetNextWindowSize({ viewport->Size.x, viewport->Size.y - s_ToolbarHeight });
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGuiWindowFlags dockspaceFlags = 0
			| ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking
			| ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse
			| ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::Begin("Master DockSpace", NULL, dockspaceFlags);
		ImGuiID dockMain = ImGui::GetID("MyDockspace");

		ImGui::DockSpace(dockMain);
		ImGui::End();
		ImGui::PopStyleVar(3);
	}
}