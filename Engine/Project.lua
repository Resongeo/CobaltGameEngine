project "Engine"
	location "%{wks.location}/Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("%{wks.location}/Engine/Build/" .. outputdir)
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "cbpch.h"
	pchsource "%{wks.location}/Engine/Source/Cobalt/cbpch.cpp"

	files
	{
		"%{wks.location}/%{prj.name}/Source/**.c",
		"%{wks.location}/%{prj.name}/Source/**.h",
		"%{wks.location}/%{prj.name}/Source/**.cpp",
		"%{wks.location}/%{prj.name}/Dependencies/glm/glm/**.hpp",
		"%{wks.location}/%{prj.name}/Dependencies/glm/glm/**.inl",
		"%{wks.location}/%{prj.name}/Dependencies/ImGui/**.h",
		"%{wks.location}/%{prj.name}/Dependencies/ImGui/**.cpp",
		"%{wks.location}/%{prj.name}/Dependencies/ImGuizmo/**.cpp",
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
		"%{IncludeDir.STBIMAGE}",
		"%{IncludeDir.ENTT}",
		"%{IncludeDir.LUA}",
		"%{IncludeDir.SOL2}",
		"%{IncludeDir.ENGINE_SRC}",
		"%{IncludeDir.COBALT}"
	}

    libdirs
    {
        "%{LibDir.GLFW}",
        "%{LibDir.LUA}",
    }

	links 
	{
		"%{Link.GLFW}",
		"%{Link.OPENGL}",
		"%{Link.DWMAPI}",
		"%{Link.LUA}",
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