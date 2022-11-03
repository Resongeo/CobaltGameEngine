#include "Application.h"

namespace Cobalt
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		Log::Init();
		s_Instance = this;
	}
}