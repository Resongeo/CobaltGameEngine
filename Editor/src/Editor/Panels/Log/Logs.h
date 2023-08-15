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
		m_Messages.push_back(LogMessage(fmt::format(format, std::forward<Args>(args)...), Color(240, 240, 240)));
	}

	template<typename ...Args>
	constexpr void AddInfo(const char* format, Args&& ...args)
	{
		m_Messages.push_back(LogMessage(fmt::format(format, std::forward<Args>(args)...), Color(102, 216, 102)));
	}

	template<typename ...Args>
	constexpr void AddWarn(const char* format, Args&& ...args)
	{
		m_Messages.push_back(LogMessage(fmt::format(format, std::forward<Args>(args)...), Color(216, 216, 54)));
	}

	template<typename ...Args>
	constexpr void AddError(const char* format, Args&& ...args)
	{
		m_Messages.push_back(LogMessage(fmt::format(format, std::forward<Args>(args)...), Color(216, 81, 81)));
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