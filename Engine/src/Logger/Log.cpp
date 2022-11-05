#include "Log.h"

namespace Cobalt
{
	Ref<spdlog::logger> Log::s_EngineLogger;
	Ref<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_EngineLogger = spdlog::stderr_color_mt("Engine");
		s_EngineLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stderr_color_mt("Client");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}