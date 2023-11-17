#include "pch.h"
#include "CobaltEditor/Managers/EditorPanelManager.h"
#include "CobaltEditor/Panels/LogPanel.h"
#include "CobaltEditor/Logger/Log.h"

namespace CobaltEditor
{
	void LogPanel::OnUIRender()
	{
		ImGui::Begin("Logs");
		
		if (ImGui::Button("Clear"))
		{
			Log::Clear();
		}
		ImGui::SameLine();
		ImGui::Checkbox("Auto Scroll", &m_ScrollToBottom);

		ImGui::BeginChild("##ScrollArea", { 0, 0 }, false, ImGuiWindowFlags_HorizontalScrollbar);

		for (auto& log : Log::GetMessages())
		{
			ImGui::TextColored(log.MessageColor, log.Message.c_str());

			if (m_ScrollToBottom && ImGui::GetScrollY() >= ImGui::GetScrollMaxY() - 10.0f)
			{
				ImGui::SetScrollHereY(1.0f);
			}
		}

		ImGui::EndChild();

		ImGui::End();
	}

	Ref<LogPanel> LogPanel::Create()
	{
		auto panel = CreateRef<LogPanel>();
		EditorPanelManager::PushPanel(panel);

		return panel;
	}
}