include "Common.lua"

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Engine/Dependencies/GLFW/include"
IncludeDir["GLAD"] = "%{wks.location}/Engine/Dependencies/GLAD/include"
IncludeDir["IMGUI"] = "%{wks.location}/Engine/Dependencies/IMGUI"
IncludeDir["IMGUIZMO"] = "%{wks.location}/Engine/Dependencies/IMGUIZMO/include"
IncludeDir["GLM"] = "%{wks.location}/Engine/Dependencies/GLM"
IncludeDir["STBIMAGE"] = "%{wks.location}/Engine/Dependencies/STBIMAGE"
IncludeDir["ENTT"] = "%{wks.location}/Engine/Dependencies/ENTT/single_include/entt"
IncludeDir["LUA"] = "%{wks.location}/Engine/Dependencies/LUA/include"
IncludeDir["SOL2"] = "%{wks.location}/Engine/Dependencies/SOL2/include"
IncludeDir["COBALT"] = "%{wks.location}/Engine/Source/Cobalt"
IncludeDir["ENGINE_SRC"] = "%{wks.location}/Engine/Source"
IncludeDir["EDITOR_SRC"] = "%{wks.location}/Editor/Source"

LibDir = {}
LibDir["GLFW"] = "%{wks.location}/Engine/Dependencies/GLFW/lib-vc2022"
LibDir["LUA"] = "%{wks.location}/Engine/Dependencies/LUA"
LibDir["ENGINE"] = "%{wks.location}/Engine/Build/" .. outputdir

Link = {}
Link["GLFW"] = "glfw3.lib"
Link["OPENGL"] = "opengl32.lib"
Link["DWMAPI"] = "dwmapi.lib"
Link["LUA"] = "lua54.lib"
Link["ENGINE"] = "Engine.lib"