#pragma once

#include "Editor/Panels/EditorPanel.h"

#include "Cobalt.h"
using namespace Cobalt;

struct LogMessage
{
	std::string Message;
	ImVec4 Color;

	LogMessage(const std::string& message, const ImVec4& color) : Message(message), Color(color) {}
};

class LogPanel : public EditorPanel
{
public:
	LogPanel();

	inline static LogPanel& Get() { return *s_Instance; }
	void Clear();

	void Update(float deltaTime) override;

	void AddLog(const std::string& message);
	void AddInfo(const std::string& message);
	void AddWarn(const std::string& message);
	void AddError(const std::string& message);

private:
	static LogPanel* s_Instance;

	bool m_ScrollToBottom = true;
	std::vector<LogMessage> m_Messages;
};

#define DEBUG_LOG(...) LogPanel::Get().AddLog(__VA_ARGS__)
#define DEBUG_INFO(...) LogPanel::Get().AddInfo(__VA_ARGS__)
#define DEBUG_WARN(...) LogPanel::Get().AddWarn(__VA_ARGS__)
#define DEBUG_ERROR(...) LogPanel::Get().AddError(__VA_ARGS__)
