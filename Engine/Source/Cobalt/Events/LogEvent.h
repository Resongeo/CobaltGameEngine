#pragma once

#include "Cobalt/Events/Event.h"

namespace Cobalt
{
	class LogTraceEvent : public Event
	{
	public:
		LogTraceEvent(const std::string& message) : m_Message(message) {}

		inline std::string GetLogMessage() const { return m_Message; }

		EVENT_CLASS_TYPE(LogTrace)
		EVENT_CLASS_CATEGORY(EventCategoryLog)

	private:
		std::string m_Message;
	};
	

	class LogInfoEvent : public Event
	{
	public:
		LogInfoEvent(const std::string& message) : m_Message(message) {}

		inline std::string GetLogMessage() const { return m_Message; }

		EVENT_CLASS_TYPE(LogInfo)
			EVENT_CLASS_CATEGORY(EventCategoryLog)

	private:
		std::string m_Message;
	};

	
	class LogWarnEvent : public Event
	{
	public:
		LogWarnEvent(const std::string& message) : m_Message(message) {}

		inline std::string GetLogMessage() const { return m_Message; }

		EVENT_CLASS_TYPE(LogWarn)
		EVENT_CLASS_CATEGORY(EventCategoryLog)

	private:
		std::string m_Message;
	};


	class LogErrorEvent : public Event
	{
	public:
		LogErrorEvent(const std::string& message) : m_Message(message) {}

		inline std::string GetLogMessage() const { return m_Message; }

		EVENT_CLASS_TYPE(LogError)
		EVENT_CLASS_CATEGORY(EventCategoryLog)

	private:
		std::string m_Message;
	};
}