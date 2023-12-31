project "Engine"
	location "%{wks.location}/Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	dependson { "GLFW", "IMGUIZMO", "IMGUI" }

	targetdir ("%{wks.location}/%{prj.name}/bin/" .. outputdir)
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "cbpch.h"
	pchsource "%{wks.location}/%{prj.name}/Source/Cobalt/cbpch.cpp"

	files
	{
		"%{wks.location}/%{prj.name}/Source/**.c",
		"%{wks.location}/%{prj.name}/Source/**.h",
		"%{wks.location}/%{prj.name}/Source/**.cpp",
		"%{wks.location}/%{prj.name}/Dependencies/glm/glm/**.hpp",
		"%{wks.location}/%{prj.name}/Dependencies/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.IMGUI}",
		"%{IncludeDir.IMGUIZMO}",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.STB}",
		"%{IncludeDir.ENTT}",
		"%{IncludeDir.LUA}",
		"%{IncludeDir.SOL2}",
		"%{IncludeDir.ENGINE_SRC}",
		"%{IncludeDir.COBALT}"
	}

    libdirs
    {
        "%{LibDir.GLFW}",
        "%{LibDir.IMGUIZMO}",
        "%{LibDir.IMGUI}",
        "%{LibDir.LUA}",
    }

	links 
	{
		"%{Link.GLFW}",
		"%{Link.IMGUIZMO}",
		"%{Link.IMGUI}",
		"%{Link.OPENGL}",
		"%{Link.DWMAPI}",
		"%{Link.LUA}",
	}

	-- Removing errors
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
		optimize "speed"

	filter "configurations:Dist"
		defines "CB_DIST"
		runtime "Release"
		optimize "speed"

	-- glad.c can't have a precompiled header
    filter "files:**.c"
        flags {"NoPCH"}