include "Scripts/Dependencies.lua"

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

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


project "Engine"
	location "Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("Engine/lib/")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "cbpch.h"
	pchsource "Engine/src/Cobalt/cbpch.cpp"

	files
	{
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/ImGui/**.h",
		"%{prj.name}/vendor/ImGui/**.cpp",
		"%{prj.name}/vendor/ImGuizmo/**.cpp",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.lua}",
		"%{IncludeDir.sol2}",
		"%{IncludeDir.src}",
		"%{IncludeDir.cobalt}"
	}

    libdirs
    {
        "%{LibDir.GLFW}",
        "%{LibDir.Lua}",
    }

	links 
	{ 
		"glfw3.lib",
		"opengl32.lib",
		"lua54.lib",
	}

	filter "system:windows"
		systemversion "latest"
		buildoptions { "/wd4312", "/wd4267", "/wd4244" }

	filter "configurations:Debug"
		defines "CB_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "CB_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "CB_DIST"
		runtime "Release"
		optimize "on"

    filter "files:**.c"
        flags {"NoPCH"}


project "Editor"
	location "Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	dependson { "Engine" }

	targetdir ("%{prj.name}/bin/")
	debugdir ("%{prj.name}/bin/")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/main.cpp",
		"%{prj.name}/src/Editor/**.h",
		"%{prj.name}/src/Editor/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.lua}",
		"%{IncludeDir.sol2}",
		"%{IncludeDir.src}",
		"%{IncludeDir.cobalt}",
		"Editor/src"
	}

    libdirs
    {
        "%{LibDir.GLFW}",
        "%{LibDir.Lua}",
		"Engine/lib"
    }

	links 
	{ 
		"Engine.lib",
		"glfw3.lib",
		"opengl32.lib",
		"dwmapi.lib",
		"lua54.lib",
	}

	filter "system:windows"
		systemversion "latest"
		buildoptions { "/wd4312", "/wd4267", "/wd4244" }
		ignoredefaultlibraries { "LIBCMT", "MSVCRT" }
		
	filter "configurations:Debug"
		defines "CB_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "CB_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "CB_DIST"
		runtime "Release"
		optimize "on"