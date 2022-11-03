#pragma once

#include "Log/Log.h"
#include "Core/Core.h"
#include "Platform/Window.h"

namespace Cobalt
{
	class Application
	{
	public:
		Application();

		void Run(){}

	private:

		static Application* s_Instance;
	};
}
