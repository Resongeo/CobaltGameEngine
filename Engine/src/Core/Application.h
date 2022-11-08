#pragma once

#include "Core/Core.h"
#include "Core/Gui.h"
#include "Events/ApplicationEvent.h"
#include "Layers/LayerStack.h"
#include "Logger/Log.h"
#include "Platform/Window.h"

namespace Cobalt
{
	class Application
	{
	public:
		Application(const WindowProperties& windowProperties);
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		static Application& Get() { return *s_Instance; }

	private:
		static Application* s_Instance;

		Scope<Window> m_Window;
		LayerStack m_LayerStack;
		bool m_Running = true;

		bool OnWindowClose(WindowCloseEvent& e);
	};
}
