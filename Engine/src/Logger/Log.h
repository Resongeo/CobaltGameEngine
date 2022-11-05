#pragma once

#include "Core/Core.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Cobalt
{
	class Log
	{
	public:
		static void Init();

		static Ref<spdlog::logger>& GetEngineLogger() { return s_EngineLogger; }
		static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static Ref<spdlog::logger> s_EngineLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};
}

#define LOG_ENGINE_TRACE(...)    ::Cobalt::Log::GetEngineLogger()->trace(__VA_ARGS__)
#define LOG_ENGINE_INFO(...)     ::Cobalt::Log::GetEngineLogger()->info(__VA_ARGS__)
#define LOG_ENGINE_WARN(...)     ::Cobalt::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define LOG_ENGINE_ERROR(...)    ::Cobalt::Log::GetEngineLogger()->error(__VA_ARGS__)
#define LOG_ENGINE_FATAL(...)	::Cobalt::Log::GetEngineLogger()->critical(__VA_ARGS__)

#define LOG_TRACE(...)			::Cobalt::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)			::Cobalt::Log::GetClientLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)			::Cobalt::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)			::Cobalt::Log::GetClientLogger()->error(__VA_ARGS__)
#define LOG_FATAL(...)			::Cobalt::Log::GetClientLogger()->critical(__VA_ARGS__)