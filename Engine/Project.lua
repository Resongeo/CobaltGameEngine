project "Engine"
	location "%{wks.location}/Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("%{wks.location}/Engine/lib/")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "cbpch.h"
	pchsource "%{wks.location}/Engine/src/Cobalt/cbpch.cpp"

	files
	{
		"%{wks.location}/%{prj.name}/src/**.c",
		"%{wks.location}/%{prj.name}/src/**.h",
		"%{wks.location}/%{prj.name}/src/**.cpp",
		"%{wks.location}/%{prj.name}/vendor/glm/glm/**.hpp",
		"%{wks.location}/%{prj.name}/vendor/glm/glm/**.inl",
		"%{wks.location}/%{prj.name}/vendor/ImGui/**.h",
		"%{wks.location}/%{prj.name}/vendor/ImGui/**.cpp",
		"%{wks.location}/%{prj.name}/vendor/ImGuizmo/**.cpp",
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