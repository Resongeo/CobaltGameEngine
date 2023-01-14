#pragma once

#include <string>

namespace Cobalt
{
	class FileSystem
	{
	public:
		static std::string OpenFileDialog(const char* filter);
		static std::string SaveFileDialog(const char* filter);
	};
}