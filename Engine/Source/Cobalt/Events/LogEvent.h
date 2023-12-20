#pragma once

#include "Cobalt/Events/Event.h"

namespace Cobalt
{
	class LogTraceEvent : public Event
	{
	public:
		LogTraceEvent(const String& message) : m_Message(message) {}

		inline String GetLogMessage() const { return m_Message; }

		EVENT_CLASS_TYPE(LogTrace)
		EVENT_CLASS_CATEGORY(EventCategoryLog)

	private:
		String m_Message;
	};
	

	class LogInfoEvent : public Event
	{
	public:
		LogInfoEvent(const String& message) : m_Message(message) {}

		inline String GetLogMessage() const { return m_Message; }

		EVENT_CLASS_TYPE(LogInfo)
			EVENT_CLASS_CATEGORY(EventCategoryLog)

	private:
		String m_Message;
	};

	
	class LogWarnEvent : public Event
	{
	public:
		LogWarnEvent(const String& message) : m_Message(message) {}

		inline String GetLogMessage() const { return m_Message; }

		EVENT_CLASS_TYPE(LogWarn)
		EVENT_CLASS_CATEGORY(EventCategoryLog)

	private:
		String m_Message;
	};


	class LogErrorEvent : public Event
	{
	public:
		LogErrorEvent(const String& message) : m_Message(message) {}

		inline String GetLogMessage() const { return m_Message; }

		EVENT_CLASS_TYPE(LogError)
		EVENT_CLASS_CATEGORY(EventCategoryLog)

	private:
		String m_Message;
	};
}