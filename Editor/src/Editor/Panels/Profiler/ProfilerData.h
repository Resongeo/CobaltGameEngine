#pragma once

#include <vector>

struct ProfilerResult
{
	const char* Name;
	float Duration;

	ProfilerResult(const char* name, float duration) : Name(name), Duration(duration) { }
};

struct ProfilerHeader
{
	const char* Name;
	std::vector<ProfilerResult> Results;

	ProfilerHeader() = default;
	ProfilerHeader(const char* name) : Name(name) { }
};