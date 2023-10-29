include "Scripts/Dependencies.lua"
include "Scripts/Common.lua"

workspace "CobaltGameEngine"
	architecture "x86_64"
	startproject "CobaltEditor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

include "Engine/Project.lua"
include "Editor/Project.lua"