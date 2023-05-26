#pragma once

#include "Cobalt.h"
using namespace Cobalt;

class Colors
{
public:
	static inline ImVec4 RGBAtoImVec4(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
	{
		return ImVec4(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
	}

	static inline ImVec4 RGBAtoImVec4(const Vec4& color)
	{
		return ImVec4(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
	}

	static inline ImU32 RGBAtoImU32(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
	{
		return ImColor(r, g, b, a);
	}

	static inline ImU32 RGBAtoImU32(const Vec4& color)
	{
		return ImColor((int)color.r, (int)color.g, (int)color.b, (int)color.a);
	}
};