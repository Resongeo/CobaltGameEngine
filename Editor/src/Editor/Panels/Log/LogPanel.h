#pragma once

#include "Editor/Panels/EditorPanel.h"
#include "Editor/Panels/Log/LogMessage.h"

#include "Cobalt.h"
using namespace Cobalt;


class LogPanel : public EditorPanel
{
public:
	LogPanel();

	static LogPanel& Get() { return *s_Instance; }
	void Clear();

	virtual void Update() override;

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
	static LogPanel* s_Instance;

	bool m_ScrollToBottom = true;
	std::vector<LogMessage> m_Messages;
};

#define DEBUG_CLEAR			LogPanel::Get().Clear()
#define DEBUG_LOG(...)		LogPanel::Get().AddLog(__VA_ARGS__)
#define DEBUG_INFO(...)		LogPanel::Get().AddInfo(__VA_ARGS__)
#define DEBUG_WARN(...)		LogPanel::Get().AddWarn(__VA_ARGS__)
#define DEBUG_ERROR(...)	LogPanel::Get().AddError(__VA_ARGS__)
