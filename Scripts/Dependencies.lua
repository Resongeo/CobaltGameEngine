IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Engine/vendor/GLFW/include"
IncludeDir["GLAD"] = "%{wks.location}/Engine/vendor/GLAD/include"
IncludeDir["IMGUI"] = "%{wks.location}/Engine/vendor/ImGui"
IncludeDir["IMGUIZMO"] = "%{wks.location}/Engine/vendor/ImGuizmo/include"
IncludeDir["GLM"] = "%{wks.location}/Engine/vendor/GLM"
IncludeDir["STBIMAGE"] = "%{wks.location}/Engine/vendor/STBIMAGE"
IncludeDir["ENTT"] = "%{wks.location}/Engine/vendor/EnTT/single_include/entt"
IncludeDir["LUA"] = "%{wks.location}/Engine/vendor/Lua/include"
IncludeDir["SOL2"] = "%{wks.location}/Engine/vendor/Sol2/include"
IncludeDir["COBALT"] = "%{wks.location}/Engine/src/Cobalt"
IncludeDir["ENGINE_SRC"] = "%{wks.location}/Engine/src"
IncludeDir["EDITOR_SRC"] = "%{wks.location}/Editor/src"

LibDir = {}
LibDir["GLFW"] = "%{wks.location}/Engine/vendor/GLFW/lib-vc2022"
LibDir["LUA"] = "%{wks.location}/Engine/vendor/Lua"
LibDir["ENGINE"] = "%{wks.location}/Engine/lib"

Link = {}
Link["GLFW"] = "glfw3.lib"
Link["OPENGL"] = "opengl32.lib"
Link["DWMAPI"] = "dwmapi.lib"
Link["LUA"] = "lua54.lib"
Link["ENGINE"] = "Engine.lib"