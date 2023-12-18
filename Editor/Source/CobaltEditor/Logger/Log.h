#pragma once

#include "CobaltEditor/Logger/LogMessage.h"

namespace CobaltEditor
{
	class Log
	{
	public:
		template<typename ...Args>
		constexpr static void Trace(std::format_string<Args...> fmt, Args&& ...args)
		{
			std::string message = std::format(fmt, std::forward<Args>(args)...);
			s_Instance->m_LogMessages.push_back(LogMessage(message, Color(245)));
		}

		template<typename ...Args>
		constexpr static void Info(std::format_string<Args...> fmt, Args&& ...args)
		{
			std::string message = std::format(fmt, std::forward<Args>(args)...);
			s_Instance->m_LogMessages.push_back(LogMessage(message, Color(101, 214, 142)));
		}

		template<typename ...Args>
		constexpr static void Warn(std::format_string<Args...> fmt, Args&& ...args)
		{
			std::string message = std::format(fmt, std::forward<Args>(args)...);
			s_Instance->m_LogMessages.push_back(LogMessage(message, Color(214, 205, 101)));
		}

		template<typename ...Args>
		constexpr static void Error(std::format_string<Args...> fmt, Args&& ...args)
		{
			std::string message = std::format(fmt, std::forward<Args>(args)...);
			s_Instance->m_LogMessages.push_back(LogMessage(message, Color(207, 83, 83)));
		}

	private:
		static void Init();
		static std::vector<LogMessage>& GetMessages() { return s_Instance->m_LogMessages; }
		static void Clear() { s_Instance->m_LogMessages.clear(); }

		friend class CobaltEditorApplication;
		friend class LogPanel;

	private:
		static Log* s_Instance;

		std::vector<LogMessage> m_LogMessages;
	};
}