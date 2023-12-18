#include "cbpch.h"

#include "Cobalt/Core/Time.h"
#include "Cobalt/Scripting/ScriptEngine.h"
#include "Cobalt/Scene/ECS/LuaEntity.h"

namespace Cobalt
{
	namespace Utils
	{
		static bool LoadScript(LuaScriptComponent& component)
		{
			if (component.Source.empty()) return false;

			component.LuaState.set_exception_handler(&Cobalt::ScriptEngine::ExceptionHandler);

			sol::protected_function_result result;

			if (component.SourceType == LuaScriptSourceType::Filepath)
				result = component.LuaState.safe_script_file(component.Source);
			else
				result = component.LuaState.safe_script(component.Source);

			if (!result.valid()) return false;
			
			component.HasScriptLoaded = true;

			return true;
		}

		static void AssignComponents(Entity entity, LuaScriptComponent& component)
		{
			component.ScriptEntity.SetLuaState(&component.LuaState);

			component.ScriptEntity.SetTransformComponent(&entity.GetComponent<TransformComponent>());

			if (entity.HasComponent<SpriteRendererComponent>())
				component.ScriptEntity.SetSpriteRendererComponent(&entity.GetComponent<SpriteRendererComponent>());
		}

		static void SetupTables(LuaScriptComponent& component)
		{
			component.ScriptEntity.OpenLibraries();

			component.ScriptEntity.SetupKeyCodesTable();
			component.ScriptEntity.SetupTransformTable();
			component.ScriptEntity.SetupDebugTable();
			component.ScriptEntity.SetupInputTable();
			component.ScriptEntity.SetupSpriteRendererTable();
		}
	}

	void ScriptEngine::RuntimeStart(Scene* scene)
	{
		auto view = scene->Registry().view<LuaScriptComponent>();
		for (auto entityID : view)
		{
			Entity entity = { entityID, scene };
			auto& scriptComponent = entity.GetComponent<LuaScriptComponent>();

			if (!Utils::LoadScript(scriptComponent)) continue;

			Utils::AssignComponents(entity, scriptComponent);
			Utils::SetupTables(scriptComponent);

			scriptComponent.LuaState["Start"]();
		}
	}

	void ScriptEngine::UpdateScripts(Scene* scene)
	{
		auto view = scene->Registry().view<LuaScriptComponent>();
		for (auto entityID : view)
		{
			Entity entity = { entityID, scene };
			auto& scriptComponent = entity.GetComponent<LuaScriptComponent>();

			if (!scriptComponent.HasScriptLoaded) continue;

			scriptComponent.LuaState["Update"](Time::deltaTime);
		}
	}

	int ScriptEngine::ExceptionHandler(lua_State* L, sol::optional<const std::exception&> maybe_exception, sol::string_view description)
	{
		if (maybe_exception)
		{
			std::cout << "(straight from the exception): ";
			const std::exception& ex = *maybe_exception;
			std::cout << ex.what() << std::endl;
		}
		else {
			std::cout << "(from the description parameter): ";
			std::cout.write(description.data(), static_cast<std::streamsize>(description.size()));
			std::cout << std::endl;
		}

		return sol::stack::push(L, description);
	}
}
