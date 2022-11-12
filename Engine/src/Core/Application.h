#pragma once

#include "Core/Core.h"
#include "Core/Gui.h"
#include "Events/ApplicationEvent.h"
#include "Layers/LayerStack.h"
#include "Logger/Log.h"
#include "Platform/Window.h"
#include "Renderer/Renderer.h"

namespace Cobalt
{
	struct ApplicationSpecification
	{
		WindowProperties WindowProperties;
		GraphicsAPI GraphicsAPI;

		ApplicationSpecification() : WindowProperties(WindowProperties), GraphicsAPI(GraphicsAPI::OpenGL) {}
	};

	class Application
	{
	public:
		Application(const ApplicationSpecification& applicationSpecifiacion);
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
