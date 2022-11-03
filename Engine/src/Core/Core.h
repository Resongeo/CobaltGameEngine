#pragma once

#include <memory>
#include <stdlib.h>
#include <unordered_map>

template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T>
using Scope = std::unique_ptr<T>;

template<typename T, typename Z>
using Dict = std::unordered_map<T, Z>;