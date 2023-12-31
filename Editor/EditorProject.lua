project "Editor"
	location "%{wks.location}/Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	dependson { "Engine" }

	targetdir ("%{wks.location}/%{prj.name}/bin/" .. outputdir)
	debugdir ("%{wks.location}/%{prj.name}/bin/" .. outputdir)
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "%{wks.location}/Editor/Source/CobaltEditor/Core/pch.cpp"

	files
	{
		"%{wks.location}/%{prj.name}/Source/main.cpp",
		"%{wks.location}/%{prj.name}/Source/pch.h",
		"%{wks.location}/%{prj.name}/Source/CobaltEditor/**.h",
		"%{wks.location}/%{prj.name}/Source/CobaltEditor/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{IncludeDir.IMGUI}",
		"%{IncludeDir.IMGUIZMO}",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.ENTT}",
		"%{IncludeDir.LUA}",
		"%{IncludeDir.SOL2}",
		"%{IncludeDir.COBALT}",
		"%{IncludeDir.ENGINE_SRC}",
		"%{IncludeDir.EDITOR_SRC}",
	}

    libdirs
    {
		"%{LibDir.ENGINE}",
    }

	links 
	{ 
		"%{Link.ENGINE}",
	}

	-- Removing errors
	filter "system:windows"
		systemversion "latest"
		buildoptions { "/wd4312", "/wd4267", "/wd4244" }
		ignoredefaultlibraries { "LIBCMT", "MSVCRT" }
		
	filter "configurations:Debug"
		defines "CB_EDITOR_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "CB_EDITOR_RELEASE"
		runtime "Release"
		optimize "speed"

	filter "configurations:Dist"
		defines "CB_EDITOR_DIST"
		runtime "Release"
		optimize "speed"