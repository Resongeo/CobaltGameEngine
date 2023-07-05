#pragma once

#include "Editor/Panels/Log/LogMessage.h"

#include "Cobalt.h"
using namespace Cobalt;

class Logs
{
public:
	static void Init();

	static Logs& Get() { return *s_Instance; }

	void Clear() { m_Messages.clear(); }
	
	std::vector<LogMessage> GetMessages() { return m_Messages; }

	template<typename ...Args>
	constexpr void AddLog(const char* format, Args&& ...args)
	{
		m_Messages.push_back(LogMessage(fmt::format(format, std::forward<Args>(args)...), ImVec4(0.94f, 0.94f, 0.94f, 1.0f)));
	}

	template<typename ...Args>
	constexpr void AddInfo(const char* format, Args&& ...args)
	{
		m_Messages.push_back(LogMessage(fmt::format(format, std::forward<Args>(args)...), ImVec4(0.40f, 0.85f, 0.40f, 1.0f)));
	}

	template<typename ...Args>
	constexpr void AddWarn(const char* format, Args&& ...args)
	{
		m_Messages.push_back(LogMessage(fmt::format(format, std::forward<Args>(args)...), ImVec4(0.85f, 0.85f, 0.21f, 1.0f)));
	}

	template<typename ...Args>
	constexpr void AddError(const char* format, Args&& ...args)
	{
		m_Messages.push_back(LogMessage(fmt::format(format, std::forward<Args>(args)...), ImVec4(0.85f, 0.32f, 0.32f, 1.0f)));
	}

private:
	static Logs* s_Instance;
	std::vector<LogMessage> m_Messages;
};

#define DEBUG_CLEAR			Logs::Get().Clear()
#define DEBUG_LOG(...)		Logs::Get().AddLog(__VA_ARGS__)
#define DEBUG_INFO(...)		Logs::Get().AddInfo(__VA_ARGS__)
#define DEBUG_WARN(...)		Logs::Get().AddWarn(__VA_ARGS__)
#define DEBUG_ERROR(...)	Logs::Get().AddError(__VA_ARGS__)