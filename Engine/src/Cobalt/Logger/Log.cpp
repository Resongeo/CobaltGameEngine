#include "cbpch.h"

#include "Cobalt/Logger/Log.h"

namespace Cobalt
{
	Ref<spdlog::logger> Log::s_EngineLogger;

	EventCallbackFn Log::s_EventCallback;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_EngineLogger = spdlog::stderr_color_mt("Engine");
		s_EngineLogger->set_level(spdlog::level::trace);
	}

	void Log::SetEventCallback(const EventCallbackFn& callback)
	{
		s_EventCallback = callback;
	}
}