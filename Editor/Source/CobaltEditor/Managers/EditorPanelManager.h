#pragma once

#include "Cobalt.h"
#include "CobaltEditor/Panels/EditorPanel.h"

namespace CobaltEditor
{
	class EditorPanelManager
	{
	public:
		static void Init();
		static void Update();
		static void UIRender();
		static void OnEvent(Event& event);

		static void PushPanel(const Shared<EditorPanel>& panel);

	private:
		static EditorPanelManager* s_Instance;
		Vector<Shared<EditorPanel>> m_Panels;
	};
}