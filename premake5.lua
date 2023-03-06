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

IncludeDir = {}
IncludeDir["GLFW"] = "Engine/vendor/GLFW/include"
IncludeDir["Glad"] = "Engine/vendor/GLAD/include"
IncludeDir["ImGui"] = "Engine/vendor/ImGui"
IncludeDir["glm"] = "Engine/vendor/GLM/include"
IncludeDir["stb_image"] = "Engine/vendor/STBIMAGE"
IncludeDir["spd_log"] = "Engine/vendor/SPDLOG/include"
IncludeDir["entt"] = "Engine/vendor/EnTT"
IncludeDir["src"] = "Engine/src"

LibDir = {}
LibDir["GLFW"] = "Engine/vendor/GLFW/lib-vc2022"


project "Engine"
	location "Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("Engine/lib/")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "cbpch.h"
	pchsource "Engine/src/cbpch.cpp"

	files
	{
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/ImGui/**.h",
		"%{prj.name}/vendor/ImGui/**.cpp",
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
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.spd_log}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.src}"
	}

    libdirs
    {
        "%{LibDir.GLFW}",
    }

	links 
	{ 
		"glfw3.lib",
		"opengl32.lib",
	}

	filter "system:windows"
		systemversion "latest"

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


project "CobaltEditor"
	location "CobaltEditor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/main.cpp",
		"%{prj.name}/Editor/**.h",
		"%{prj.name}/Editor/**.cpp"
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
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.spd_log}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.src}",
		"CobaltEditor"
	}

    libdirs
    {
        "%{LibDir.GLFW}",
		"Engine/lib"
    }

	links 
	{ 
		"Engine.lib",
		"glfw3.lib",
		"opengl32.lib",
		"dwmapi.lib"
	}

	filter "system:windows"
		systemversion "latest"
		
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