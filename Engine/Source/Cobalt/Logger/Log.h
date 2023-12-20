#pragma once

#include "Cobalt/Core/Core.h"
#include "Cobalt/Events/Event.h"
#include "Cobalt/Events/LogEvent.h"

#include <iostream>
#include <format>
#include <chrono>

namespace Cobalt
{
	class Log
	{
	public:
		static void Init();

		static void SetEventCallback(const EventCallbackFn& callback);
		static Log* Get() { return s_Instance; }

		template<typename ...Args>
		constexpr void Trace(std::format_string<Args...> fmt, Args&& ...args)
		{
			String message = std::format(fmt, std::forward<Args>(args)...);
			std::cout << GetPrefix("TRACE", CONSOLE_COLOR_WHITE) << message << "\n" << CONSOLE_RESET;
		
			LogTraceEvent event(message);
			m_EventCallback(event);
		}

		template<typename ...Args>
		constexpr void Info(std::format_string<Args...> fmt, Args&& ...args)
		{
			String message = std::format(fmt, std::forward<Args>(args)...);
			std::cout << GetPrefix("INFO", CONSOLE_COLOR_GREEN) << message << "\n" << CONSOLE_RESET;

			LogInfoEvent event(message);
			m_EventCallback(event);
		}

		template<typename ...Args>
		constexpr void Warn(std::format_string<Args...> fmt, Args&& ...args)
		{
			String message = std::format(fmt, std::forward<Args>(args)...);
			std::cout << GetPrefix("WARN", CONSOLE_COLOR_YELLOW) << message << "\n" << CONSOLE_RESET;

			LogWarnEvent event(message);
			m_EventCallback(event);
		}

		template<typename ...Args>
		constexpr void Error(std::format_string<Args...> fmt, Args&& ...args)
		{
			String message = std::format(fmt, std::forward<Args>(args)...);
			std::cout << GetPrefix("ERROR", CONSOLE_COLOR_RED) << message << "\n" << CONSOLE_RESET;

			LogErrorEvent event(message);
			m_EventCallback(event);
		}

	private:
		std::string GetPrefix(const char* level, const char* color)
		{
			auto now = std::chrono::system_clock::now();
			auto currentTime = std::chrono::system_clock::to_time_t(now);
			auto localTime = std::localtime(&currentTime);

			int hour = localTime->tm_hour;
			int minute = localTime->tm_min;
			int second = localTime->tm_sec;

			m_OddMessageCount = !m_OddMessageCount;

			return std::format("{}{}[{} - {}:{}:{}]: {}{}", color, CONSOLE_BOLD_TEXT, level, hour, minute, second, CONSOLE_RESET, m_OddMessageCount ? CONSOLE_COLOR_GRAY : CONSOLE_COLOR_LIGHT_GRAY);
		}

	private:
		const char* CONSOLE_COLOR_WHITE = "\x1b[97m";
		const char* CONSOLE_COLOR_GREEN = "\x1b[92m";
		const char* CONSOLE_COLOR_YELLOW = "\x1b[93m";
		const char* CONSOLE_COLOR_RED = "\x1b[91m";
		const char* CONSOLE_COLOR_LIGHT_GRAY = "\x1b[37m";
		const char* CONSOLE_COLOR_GRAY = "\x1b[90m";
		const char* CONSOLE_BOLD_TEXT = "\x1b[1m";
		const char* CONSOLE_RESET = "\x1b[0m";

	private:
		static Log* s_Instance;

		EventCallbackFn m_EventCallback;
		bool m_OddMessageCount = true;
	};

	#define LOG_TRACE(...)	Log::Get()->Trace(__VA_ARGS__)
	#define LOG_INFO(...)	Log::Get()->Info(__VA_ARGS__)
	#define LOG_WARN(...)	Log::Get()->Warn(__VA_ARGS__)
	#define LOG_ERROR(...)	Log::Get()->Error(__VA_ARGS__)
}