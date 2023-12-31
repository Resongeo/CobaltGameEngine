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

include "Engine/EngineProject.lua"
include "Editor/EditorProject.lua"

include "Engine/Dependencies/Projects/ImGuizmo.lua"
include "Engine/Dependencies/Projects/ImGui.lua"
include "Engine/Dependencies/GLFW"