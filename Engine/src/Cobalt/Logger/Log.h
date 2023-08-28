#pragma once

#include "Cobalt/Core/Core.h"
#include "Cobalt/Events/Event.h"
#include "Cobalt/Events/LogEvent.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Cobalt
{
	class Log
	{
	public:
		static void Init();

		static Ref<spdlog::logger>& GetEngineLogger() { return s_EngineLogger; }

		static void SetEventCallback(const EventCallbackFn& callback);

		template<typename ...Args>
		static void DispatchLogTraceEvent(const char* format, Args&& ...args)
		{
			LogTraceEvent event(fmt::format(format, std::forward<Args>(args)...));
			s_EventCallback(event);
		}
		template<typename ...Args>
		static void DispatchLogInfoEvent(const char* format, Args&& ...args)
		{
			LogInfoEvent event(fmt::format(format, std::forward<Args>(args)...));
			s_EventCallback(event);
		}
		template<typename ...Args>
		static void DispatchLogWarnEvent(const char* format, Args&& ...args)
		{
			LogWarnEvent event(fmt::format(format, std::forward<Args>(args)...));
			s_EventCallback(event);
		}
		template<typename ...Args>
		static void DispatchLogErrorEvent(const char* format, Args&& ...args)
		{
			LogErrorEvent event(fmt::format(format, std::forward<Args>(args)...));
			s_EventCallback(event);
		}

	private:
		static Ref<spdlog::logger> s_EngineLogger;

		static EventCallbackFn s_EventCallback;
	};
}

#define COBALT_TRACE(...)	::Cobalt::Log::GetEngineLogger()->trace(__VA_ARGS__);	::Cobalt::Log::DispatchLogTraceEvent(__VA_ARGS__)
#define COBALT_INFO(...)	::Cobalt::Log::GetEngineLogger()->info(__VA_ARGS__);	::Cobalt::Log::DispatchLogInfoEvent(__VA_ARGS__)
#define COBALT_WARN(...)    ::Cobalt::Log::GetEngineLogger()->warn(__VA_ARGS__);	::Cobalt::Log::DispatchLogWarnEvent(__VA_ARGS__)
#define COBALT_ERROR(...)	::Cobalt::Log::GetEngineLogger()->error(__VA_ARGS__);	::Cobalt::Log::DispatchLogErrorEvent(__VA_ARGS__)
#define COBALT_FATAL(...)	::Cobalt::Log::GetEngineLogger()->critical(__VA_ARGS__)