#include "Application.h"

namespace Cobalt
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application(const ApplicationSpecification& applicationSpecifiacion)
	{
		Log::Init();
		s_Instance = this;

		Renderer::SetAPI(applicationSpecifiacion.GraphicsAPI);
		LOG_ENGINE_INFO("Renderer API: {0}", Renderer::GetAPIString());

		m_Window = CreateScope<Window>(applicationSpecifiacion.WindowProperties);
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
			m_Time = (float)glfwGetTime();
			m_DeltaTime = m_Time - m_LastFrameTime;
			m_LastFrameTime = m_Time;

			Gui::NewFrame();

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate(m_DeltaTime);
			}

			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiUpdate(m_DeltaTime);
			}

			Gui::Render();
			m_Window->Update();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

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

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		RenderCommand::SetViewport(0, 0, e.GetWidth(), e.GetHeight());
		return false;
	}
}