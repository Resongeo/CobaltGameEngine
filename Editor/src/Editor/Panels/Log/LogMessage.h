#pragma once

#include "Cobalt.h"
using namespace Cobalt;

#include <string>

struct LogMessage
{
	std::string Message;
	ImVec4 Color;

	LogMessage(const std::string& message, const ImVec4& color) : Message(message), Color(color) {}
};