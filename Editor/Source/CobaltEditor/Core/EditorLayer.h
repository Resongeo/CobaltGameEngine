#pragma once

#include "Cobalt.h"
using namespace Cobalt;

namespace CobaltEditor
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer() : Layer("Cobalt Editor Layer") {}

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnImGuiUpdate() override;
		void OnEvent(Event& event) override;

	private:
		bool OnLogEvent(LogEvent e);

	private:
		Shared<Window> m_Window;
		Shared<Scene> m_Scene;
	};
}