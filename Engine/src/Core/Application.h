#pragma once

#include "Core/Core.h"
#include "Events/ApplicationEvent.h"
#include "Log/Log.h"
#include "Platform/Window.h"

namespace Cobalt
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

	private:
		Window m_Window;
		static Application* s_Instance;

		bool m_Running = true;

		bool OnWindowClose(WindowCloseEvent& e);
	};
}
