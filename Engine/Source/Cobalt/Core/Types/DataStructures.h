#pragma once

#include <array>
#include <vector>
#include <unordered_map>

namespace Cobalt
{
	template<typename T, size_t N>
	using Array = std::array<T, N>;

	template<typename T>
	using Vector = std::vector<T>;

	template<typename T>
	using InitializerList = std::initializer_list<T>;

	template<typename K, typename V>
	using HashMap = std::unordered_map<K, V>;
}