#include "pch.h"
#include "CobaltEditor/Components/DockSpace.h"

namespace CobaltEditor
{
	void DockSpace::MasterSpace()
	{
		auto viewport = ImGui::GetMainViewport();
		auto topbarHeight = StyleManager::GetSizes().Toolbar.TopbarHeight;

		ImGui::SetNextWindowPos({ viewport->Pos.x, viewport->Pos.y + topbarHeight });
		ImGui::SetNextWindowSize({ viewport->Size.x, viewport->Size.y - topbarHeight });
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGuiWindowFlags dockspaceFlags = 0
			| ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoDocking
			| ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse
			| ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoBringToFrontOnFocus;

		ScopedStyleVars _
		({
			{ ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f) },
			{ ImGuiStyleVar_WindowRounding, 0.0f },
			{ ImGuiStyleVar_WindowBorderSize, 0.0f },
		});

		ImGui::Begin("Master DockSpace", NULL, dockspaceFlags);
		{
			ImGui::DockSpace(ImGui::GetID("MyDockspace"));
		}
		ImGui::End();
	}
}