#pragma once

#include "Core/Core.h"
#include "Events/ApplicationEvent.h"
#include "Layers/LayerStack.h"
#include "Logger/Log.h"
#include "Platform/Window.h"

namespace Cobalt
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	private:
		static Application* s_Instance;

		Window m_Window;
		LayerStack m_LayerStack;
		bool m_Running = true;

		bool OnWindowClose(WindowCloseEvent& e);
	};
}
