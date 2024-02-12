#include "cbpch.h"

#include "Cobalt/Core/Application.h"
#include "Cobalt/Scene/SceneManager.h"
#include "Cobalt/Input/Input.h"
#include "Cobalt/Gui/Gui.h"
#include "Cobalt/Layers/LayerStack.h"

namespace Cobalt
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application(const ApplicationSpecification& appSpecs)
	{
		s_Instance = this;
		
		Log::Init();
		Log::SetEventCallback(BIND_EVENT_FN(OnEvent));

		Random::Init();

		m_LayerStack = CreateUnique<LayerStack>();

		m_Window = Window::Create(appSpecs.WindowProps);
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		SceneManager::Init();
		RenderCommand::Init();
		Input::Init();
		Gui::Init();
	}

	Application::~Application()
	{
		for (Layer* layer : *m_LayerStack)
		{
			layer->OnDetach();
		}

		Gui::ShutDown();
		m_Window->Destroy();
	}

	void Application::Run()
	{
		while (m_Running)
		{
			Time::Update();
			Gui::NewFrame();

			for (Layer* layer : *m_LayerStack)
			{
				layer->OnUpdate();
			}

			for (Layer* layer : *m_LayerStack)
			{
				layer->OnImGuiUpdate();
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

		for (Layer* layer : *m_LayerStack)
		{
			layer->OnEvent(e);
			if (e.Handled) break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack->PushLayer(layer);
		layer->OnAttach();

		LOG_INFO("{} attached!", layer->GetName());
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack->PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::Close()
	{
		s_Instance->m_Running = false;
	}

	void Application::Restart()
	{
		PlatformUtils::RestartApplication();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		RenderCommand::SetViewport(0, 0, e.GetWidth(), e.GetHeight());
		return true;
	}
}