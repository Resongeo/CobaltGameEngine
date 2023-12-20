#pragma once

#include <stdlib.h>
#include <functional>
#include <sstream>
#include <fstream>
#include <filesystem>

namespace Cobalt
{
#ifdef _WIN64
	typedef unsigned long long	size;
#else
	typedef unsigned int		size;
#endif

	typedef char		i8;
	typedef short		i16;
	typedef int			i32;
	typedef long long	i64;

	typedef unsigned char		u8;
	typedef unsigned short		u16;
	typedef unsigned int		u32;
	typedef unsigned long long	u64;

	#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

	#define BIT(x) (1 << x)

	#define OPENGL_VERSION_MAJOR 4
	#define OPENGL_VERSION_MINOR 5
	#define OPENGL_VERSION_STRING "#version 450"
	#define OPENGL_PROFILE GLFW_OPENGL_CORE_PROFILE
}