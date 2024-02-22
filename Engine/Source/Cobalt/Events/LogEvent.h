#pragma once

#include "Cobalt/Events/Event.h"

namespace Cobalt
{
	enum class LogEventType
	{
		Trace = 0,
		Info,
		Warn,
		Error
	};

	class LogEvent : public Event
	{
	public:
		LogEvent(const String& message, LogEventType type) : m_Message(message), m_Type(type) {}

		inline String GetLogMessage() const { return m_Message; }
		inline LogEventType GetLogType() const { return m_Type; }

		EVENT_CLASS_TYPE(Log)
		EVENT_CLASS_CATEGORY(EventCategoryLog)

	private:
		String m_Message;
		LogEventType m_Type;
	};
}