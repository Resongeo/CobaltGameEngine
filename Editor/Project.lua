project "Editor"
	location "%{wks.location}/Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	dependson { "Engine" }

	targetdir ("%{wks.location}/%{prj.name}/bin/")
	debugdir ("%{wks.location}/%{prj.name}/bin/")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{wks.location}/%{prj.name}/src/main.cpp",
		"%{wks.location}/%{prj.name}/src/CobaltEditor/**.h",
		"%{wks.location}/%{prj.name}/src/CobaltEditor/**.cpp"
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