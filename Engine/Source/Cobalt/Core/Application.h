#pragma once

#include "Cobalt/Core/Fwd.h"
#include "Cobalt/Core/Types.h"
#include "Cobalt/Platform/Window.h"
#include "Cobalt/Layers/LayerStack.h"

namespace Cobalt
{
	struct ApplicationSpecification
	{
		WindowProperties WindowProps;

		ApplicationSpecification() : WindowProps(WindowProperties()) {}
	};

	class Application
	{
	public:
		Application(const ApplicationSpecification& appSpecs);
		
		void Run();

		void PushLayer(Unique<Layer> layer);

		static void Close();
		static void Restart();

		static Shared<Window>& GetWindow() { return s_Instance->m_Window; }

	private:
		void OnEvent(Event& e);
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		static Application* s_Instance;

		Shared<Window> m_Window;
		LayerStack m_LayerStack;
		
		bool m_Running = true;
	};
}
