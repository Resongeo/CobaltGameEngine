#pragma once

#include "Cobalt/Core/Types/Math.h"
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
		Color(uint8_t uniform, uint8_t alpha = 255) : r(uniform / 255.0f), g(uniform / 255.0f), b(uniform / 255.0f), a(alpha / 255.0f) {}
		Color(uint8_t R, uint8_t G, uint8_t B, uint8_t A = 255) : r(R / 255.0f), g(G / 255.0f), b(B / 255.0f), a(A / 255.0f) {}

		operator Vec3() { return Vec3(r, g, b); }
		operator Vec3() const { return Vec3(r, g, b); }

		operator Vec4() { return Vec4(r, g, b, a); }
		operator Vec4() const { return Vec4(r, g, b, a); }

		operator ImVec4() { return ImVec4(r, g, b, a); }
		operator ImVec4() const { return ImVec4(r, g, b, a); }

		operator uint32_t() const
		{
			uint8_t R = static_cast<uint8_t>(255.f * r);
			uint8_t G = static_cast<uint8_t>(255.f * g);
			uint8_t B = static_cast<uint8_t>(255.f * b);
			uint8_t A = static_cast<uint8_t>(255.f * a);

			return (A << 24) | (B << 16) | (G << 8) | R;
		}

		operator float* () { return &r; }
	};
}