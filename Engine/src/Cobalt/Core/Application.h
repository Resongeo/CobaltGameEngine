#pragma once

#include "Cobalt/Core/Core.h"
#include "Cobalt/Core/Time.h"
#include "Cobalt/Core/Random.h"
#include "Cobalt/Gui/Gui.h"

#include "Cobalt/Events/ApplicationEvent.h"
#include "Cobalt/Layers/LayerStack.h"
#include "Cobalt/Input/Input.h"
#include "Cobalt/Logger/Log.h"
#include "Cobalt/Platform/Window.h"

#include "Cobalt/Renderer/Renderer.h"
#include "Cobalt/Renderer/RenderCommand.h"

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
		static Ref<Window>& GetWindow() { return s_Instance->m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		static Application* s_Instance;

		Ref<Window> m_Window;
		LayerStack m_LayerStack;
		bool m_Running = true;
	};
}
