#include "Application.h"

namespace Cobalt
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application(const WindowProperties& windowProperties)
	{
		Log::Init();
		s_Instance = this;

		m_Window.reset(new Window(windowProperties));
		m_Window->Create();
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		Gui::Init(m_Window->GetHandle());
	}

	Application::~Application()
	{
		Gui::Destroy();
	}

	void Application::Run()
	{
		while (m_Running)
		{
			Gui::NewFrame();

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			Gui::Render();
			m_Window->Update();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled) break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}