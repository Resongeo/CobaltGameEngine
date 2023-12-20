#pragma once

#include "Cobalt.h"
using namespace Cobalt;

namespace CobaltEditor
{
	struct LogMessage
	{
		String Message;
		Color MessageColor;

		LogMessage(const String& message, const Color& color) : Message(message), MessageColor(color) { }
	};
}