#pragma once

#include <memory>
#include <stdlib.h>
#include <unordered_map>
#include <vector>
#include <array>
#include <functional>
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>

template<typename T>
using Ref = std::shared_ptr<T>;
template<typename T, typename ... Args>
constexpr Ref<T> CreateRef(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

template<typename T>
using Scope = std::unique_ptr<T>;
template<typename T, typename ... Args>
constexpr Scope<T> CreateScope(Args&& ... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

#define CB_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#define BIT(x) (1 << x)

#define COBALT_OPENGL_VERSION_MAJOR 4
#define COBALT_OPENGL_VERSION_MINOR 5
#define COBALT_OPENGL_VERSION_STRING "#version 450"
#define COBALT_OPENGL_PROFILE GLFW_OPENGL_CORE_PROFILE