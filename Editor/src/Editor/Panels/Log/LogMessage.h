#pragma once

#include "Cobalt.h"
using namespace Cobalt;

#include <string>

struct LogMessage
{
	std::string Message;
	Color TextColor;

	LogMessage(const std::string& message, const Color& textColor) : Message(message), TextColor(textColor) { }
};