project "IMGUIZMO"
	location "%{wks.location}/Engine/Dependencies/IMGUIZMO"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("../%{prj.name}/bin/" .. outputdir)
	objdir ("../%{prj.name}/bin-int/" .. outputdir)

    files
    {
        "../%{prj.name}/ImGuizmo.cpp",
        "../%{prj.name}/ImGuizmo.h",
    }

    includedirs
    {
		"%{IncludeDir.IMGUI}",
    }

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "speed"

    filter "configurations:Dist"
        runtime "Release"
        optimize "speed"