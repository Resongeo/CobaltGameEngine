#include "Application.h"

namespace Cobalt
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		Log::Init();
		s_Instance = this;
		m_Window.Create();
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (!m_Window.ShouldClose())
		{
			glfwPollEvents();
			m_Window.SwapBuffers();
		}
	}
}