#pragma once

#include "Cobalt/Core/Types/String.h"
#include <fstream>

namespace Cobalt
{
	struct Buffer
	{
		uint8_t* Data = nullptr;
		size_t Size = 0;

		Buffer() = default;
		Buffer(const Buffer&) = default;

		static Buffer FromFile(const String& filepath)
		{
			std::ifstream stream(filepath, std::ios::binary | std::ios::ate);
			if (!stream)
			{
				return Buffer();
			}

			std::streampos end = stream.tellg();
			stream.seekg(0, std::ios::beg);
			uint32_t size = end - stream.tellg();

			if (size == 0)
			{
				return Buffer();
			}

			char* buffer = new char[size];
			stream.read((char*)buffer, size);
			stream.close();

			Buffer result;
			result.Data = (uint8_t*)buffer;
			result.Size = size;
			return result;
		}

		void Release()
		{
			delete[] Data;
			Data = nullptr;
			Size = 0;
		}

		template<typename T>
		T* As()
		{
			return (T*)Data;
		}
	};
}