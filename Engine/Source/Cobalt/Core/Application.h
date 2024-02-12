#pragma once

#include "Cobalt/Core/Types.h"
#include "Cobalt/Core/Fwd.h"
#include "Cobalt/Graphics/GraphicsAPI.h"
#include "Cobalt/Platform/Window.h"

namespace Cobalt
{
	struct ApplicationSpecification
	{
		WindowProperties WindowProps;
		GraphicsAPI GraphicsAPI;

		ApplicationSpecification() : WindowProps(WindowProperties()), GraphicsAPI(GraphicsAPI::OpenGL) {}
	};

	class Application
	{
	public:
		Application(const ApplicationSpecification& appSpecs);
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		static void Close();
		static void Restart();

		static Application& Get() { return *s_Instance; }
		static Shared<Window>& GetWindow() { return s_Instance->m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		static Application* s_Instance;

		Unique<LayerStack> m_LayerStack;
		Shared<Window> m_Window;
		bool m_Running = true;
	};
}
