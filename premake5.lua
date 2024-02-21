include "Tools/Dependencies.lua"
include "Tools/Common.lua"

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

include "Engine"
include "Editor"
include "ScriptCore"

include "Engine/Dependencies/Projects/ImGuizmo.lua"
include "Engine/Dependencies/Projects/ImGui.lua"
include "Engine/Dependencies/GLFW"