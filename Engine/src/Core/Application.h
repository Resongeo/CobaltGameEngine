#pragma once

#include "Core/Core.h"
#include "Core/Time.h"
#include "Gui/Gui.h"

#include "Events/ApplicationEvent.h"
#include "Layers/LayerStack.h"
#include "Logger/Log.h"
#include "Platform/Window.h"

#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"

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

		Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		static Application* s_Instance;

		Scope<Window> m_Window;
		LayerStack m_LayerStack;
		bool m_Running = true;
	};
}
