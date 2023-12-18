#pragma once

#include "Cobalt.h"
using namespace Cobalt;

namespace CobaltEditor
{
	struct LogMessage
	{
		std::string Message;
		Color MessageColor;

		LogMessage(const std::string& message, const Color& color) : Message(message), MessageColor(color) { }
	};
}