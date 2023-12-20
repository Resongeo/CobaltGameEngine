#pragma once

#include "Cobalt/Core/Types/String.h"

namespace Cobalt
{
	class FileSystem
	{
	public:
		static String OpenFileDialog(const char* filter);
		static String SaveFileDialog(const char* filter);
	};
}