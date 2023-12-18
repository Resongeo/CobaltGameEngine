#pragma once

#include "CobaltEditor/Panels/EditorPanel.h"

namespace CobaltEditor
{
	class LogPanel : public EditorPanel
	{
	public:
		void OnUIRender() override;

		static Ref<LogPanel> Create();

	private:
		bool m_ScrollToBottom = true;
	};
}