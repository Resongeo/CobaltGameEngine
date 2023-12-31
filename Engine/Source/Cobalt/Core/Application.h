#pragma once

#include "Cobalt/Core/Types/Memory.h"
#include "Cobalt/Layers/LayerStack.h"
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
