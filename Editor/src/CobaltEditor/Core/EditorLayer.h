#pragma once

#include "Cobalt.h"

namespace CobaltEditor
{
	class EditorLayer : public Cobalt::Layer
	{
	public:
		EditorLayer() : Layer("Cobalt Editor Layer") {}

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnImGuiUpdate() override;
		void OnEvent(Cobalt::Event& event) override;

	private:
		Ref<Cobalt::Window> m_Window;
		Ref<Cobalt::Scene> m_Scene;
	};
}