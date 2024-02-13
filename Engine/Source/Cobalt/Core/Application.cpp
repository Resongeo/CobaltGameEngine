#include "cbpch.h"

#include "Cobalt/Core/Application.h"
#include "Cobalt/Scene/SceneManager.h"
#include "Cobalt/Input/Input.h"
#include "Cobalt/Gui/Gui.h"

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

		m_Window = Window::Create(appSpecs.WindowProps);
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		SceneManager::Init();
		RenderCommand::Init();
		Input::Init();
		Gui::Init();
	}

	Application::~Application()
	{
		for (const auto& layer : m_LayerStack.GetLayers())
		{
			layer->OnDetach();
		}

		Gui::ShutDown();
		m_Window->Destroy();
	}

	void Application::Run()
	{
		for (const auto& layer : m_LayerStack.GetLayers())
		{
			layer->OnAttach();
			LOG_INFO("{} attached", layer->GetName());
		}

		while (m_Running)
		{
			Time::Update();
			Gui::NewFrame();

			for (const auto& layer : m_LayerStack.GetLayers())
			{
				layer->OnUpdate();
			}

			for (const auto& layer : m_LayerStack.GetLayers())
			{
				layer->OnImGuiUpdate();
			}

			Gui::Render();
			m_Window->Update();
		}

		for (const auto& layer : m_LayerStack.GetLayers())
		{
			layer->OnDetach();
			LOG_INFO("{} detached", layer->GetName());
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

		for (const auto& layer : m_LayerStack.GetLayers())
		{
			layer->OnEvent(e);
			if (e.Handled) break;
		}
	}

	void Application::PushLayer(Unique<Layer> layer)
	{
		m_LayerStack.PushLayer(std::move(layer));
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