project "ScriptCore"
    kind "SharedLib"
    language "C#"
    dotnetframework "4.7.2"

    targetname ("Cobalt-ScriptCore")
	targetdir ("%{wks.location}/Editor/Resources/")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "Source/**.cs",
        "Properties/**.cs",
    }

    
    filter "configurations:Debug"
        runtime "Debug"
        optimize "Off"
        symbols "Default"
        
    filter "configurations:Release"
        runtime "Release"
        optimize "Full"
        symbols "Off"