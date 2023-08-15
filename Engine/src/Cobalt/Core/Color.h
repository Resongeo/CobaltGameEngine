#pragma once

#include "Cobalt/Core/Math.h"
#include <imgui.h>

namespace Cobalt
{
	struct Color
	{
		float r = 1.0f;
		float g = 1.0f;
		float b = 1.0f;
		float a = 1.0f;

		Color() = default;
		Color(const Color&) = default;
		Color(const Vec3& color) : r(color.x), g(color.y), b(color.z) {}
		Color(const Vec4& color) : r(color.r), g(color.g), b(color.b), a(color.a) {}
		Color(float uniform) : r(uniform), g(uniform), b(uniform) {}
		Color(uint8_t R, uint8_t G, uint8_t B) : r(R / 255.0f), g(G / 255.0f), b(B / 255.0f) { }
		Color(uint8_t R, uint8_t G, uint8_t B, uint8_t A) : r(R / 255.0f), g(G / 255.0f), b(B / 255.0f), a(A / 255.0f) { }

		operator Vec3() { return Vec3(r, g, b); }
		operator Vec3() const { return Vec3(r, g, b); }

		operator Vec4() { return Vec4(r, g, b, a); }
		operator Vec4() const { return Vec4(r, g, b, a); }

		operator ImVec4() { return ImVec4(r, g, b, a); }
		operator ImVec4() const { return ImVec4(r, g, b, a); }

		operator ImU32() { return ImColor(r, g, b, a); }
		operator ImU32() const { return ImColor(r, g, b, a); }

		operator float* () { return &r; }
	};
}