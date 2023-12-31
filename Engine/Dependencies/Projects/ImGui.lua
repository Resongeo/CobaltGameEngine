project "IMGUI"
    location "%{wks.location}/Engine/Dependencies/IMGUI"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

	targetdir ("../%{prj.name}/bin/" .. outputdir)
	objdir ("../%{prj.name}/bin-int/" .. outputdir)

    files
	{
		"../%{prj.name}/imconfig.h",
		"../%{prj.name}/imgui.h",
		"../%{prj.name}/imgui.cpp",
		"../%{prj.name}/imgui_draw.cpp",
		"../%{prj.name}/imgui_internal.h",
		"../%{prj.name}/imgui_tables.cpp",
		"../%{prj.name}/imgui_widgets.cpp",
		"../%{prj.name}/imstb_rectpack.h",
		"../%{prj.name}/imstb_textedit.h",
		"../%{prj.name}/imstb_truetype.h",
		"../%{prj.name}/imgui_demo.cpp",
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