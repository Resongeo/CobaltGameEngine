include "Common.lua"

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Engine/Dependencies/GLFW/include"
IncludeDir["GLAD"] = "%{wks.location}/Engine/Dependencies/GLAD/include"
IncludeDir["IMGUI"] = "%{wks.location}/Engine/Dependencies/IMGUI"
IncludeDir["IMGUIZMO"] = "%{wks.location}/Engine/Dependencies/IMGUIZMO"
IncludeDir["GLM"] = "%{wks.location}/Engine/Dependencies/GLM"
IncludeDir["STB"] = "%{wks.location}/Engine/Dependencies/STB"
IncludeDir["ENTT"] = "%{wks.location}/Engine/Dependencies/ENTT/single_include/entt"
IncludeDir["COBALT"] = "%{wks.location}/Engine/Source/Cobalt"
IncludeDir["ENGINE_SRC"] = "%{wks.location}/Engine/Source"
IncludeDir["EDITOR_SRC"] = "%{wks.location}/Editor/Source"

LibDir = {}
LibDir["GLFW"] = "%{wks.location}/Engine/Dependencies/GLFW/bin/" .. outputdir .. "/GLFW"
LibDir["IMGUIZMO"] = "%{wks.location}/Engine/Dependencies/IMGUIZMO/bin/" .. outputdir
LibDir["IMGUI"] = "%{wks.location}/Engine/Dependencies/IMGUI/bin/" .. outputdir
LibDir["ENGINE"] = "%{wks.location}/Engine/bin/" .. outputdir

Link = {}
Link["GLFW"] = "GLFW.lib"
Link["IMGUIZMO"] = "IMGUIZMO.lib"
Link["IMGUI"] = "IMGUI.lib"
Link["OPENGL"] = "opengl32.lib"
Link["DWMAPI"] = "dwmapi.lib"
Link["ENGINE"] = "Engine.lib"