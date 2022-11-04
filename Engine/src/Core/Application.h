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

	private:
		Window m_Window;
		static Application* s_Instance;
	};
}
