#include "cbpch.h"
#include "Cobalt/Core/Time.h"
#include "Cobalt/Scripting/ScriptEngine.h"
#include "Cobalt/Scene/ECS/LuaEntity.h"

namespace Cobalt
{
	void ScriptEngine::RuntimeStart(Scene* scene)
	{
		auto view = scene->Registry().view<LuaScriptComponent>();
		for (auto entityID : view)
		{
			Entity entity = { entityID, scene };
			auto& scriptComponent = entity.GetComponent<LuaScriptComponent>();

			if (scriptComponent.Source.empty()) continue;

			scriptComponent.LuaState.set_exception_handler(&ScriptEngine::ExceptionHandler);

			auto result = scriptComponent.LuaState.safe_script_file(scriptComponent.Source);
			if (result.valid())
				scriptComponent.HasScriptLoaded = true;
			else continue;

			scriptComponent.ScriptEntity.SetTransformComponent(&entity.GetComponent<TransformComponent>());

			if(entity.HasComponent<SpriteRendererComponent>())
				scriptComponent.ScriptEntity.SetSpriteRendererComponent(&entity.GetComponent<SpriteRendererComponent>());

			scriptComponent.LuaState.open_libraries(sol::lib::base);
			scriptComponent.LuaState.open_libraries(sol::lib::math);
			scriptComponent.LuaState.open_libraries(sol::lib::string);

			auto transformTable = scriptComponent.LuaState["Transform"].get_or_create<sol::table>();
			transformTable.set_function("GetPositionX",	&LuaEntity::GetPositionX, &scriptComponent.ScriptEntity);
			transformTable.set_function("GetPositionY",	&LuaEntity::GetPositionY, &scriptComponent.ScriptEntity);
			transformTable.set_function("GetPositionZ",	&LuaEntity::GetPositionZ, &scriptComponent.ScriptEntity);

			transformTable.set_function("SetPosition",	&LuaEntity::SetPosition, &scriptComponent.ScriptEntity);
			transformTable.set_function("SetPositionX",	&LuaEntity::SetPositionX, &scriptComponent.ScriptEntity);
			transformTable.set_function("SetPositionY",	&LuaEntity::SetPositionY, &scriptComponent.ScriptEntity);
			transformTable.set_function("SetPositionZ",	&LuaEntity::SetPositionZ, &scriptComponent.ScriptEntity);
			
			transformTable.set_function("RotateX",		&LuaEntity::RotateX, &scriptComponent.ScriptEntity);
			transformTable.set_function("RotateY",		&LuaEntity::RotateY, &scriptComponent.ScriptEntity);
			transformTable.set_function("RotateZ",		&LuaEntity::RotateZ, &scriptComponent.ScriptEntity);

			transformTable.set_function("Translate",	&LuaEntity::Translate, &scriptComponent.ScriptEntity);
			transformTable.set_function("TranslateX",	&LuaEntity::TranslateX, &scriptComponent.ScriptEntity);
			transformTable.set_function("TranslateY",	&LuaEntity::TranslateY, &scriptComponent.ScriptEntity);
			transformTable.set_function("TranslateZ",	&LuaEntity::TranslateZ, &scriptComponent.ScriptEntity);

			auto debugTable = scriptComponent.LuaState["Debug"].get_or_create<sol::table>();
			debugTable.set_function("Log", &LuaEntity::Log, &scriptComponent.ScriptEntity);
			debugTable.set_function("Info", &LuaEntity::Info, &scriptComponent.ScriptEntity);
			debugTable.set_function("Warn", &LuaEntity::Warn, &scriptComponent.ScriptEntity);
			debugTable.set_function("Error", &LuaEntity::Error, &scriptComponent.ScriptEntity);

			auto inputTable = scriptComponent.LuaState["Input"].get_or_create<sol::table>();
			inputTable.set_function("IsMouseButtonClicked", &LuaEntity::IsMouseButtonClicked, &scriptComponent.ScriptEntity);
			inputTable.set_function("IsKeyDown", &LuaEntity::IsKeyDown, &scriptComponent.ScriptEntity);

			auto spriteTable = scriptComponent.LuaState["SpriteRenderer"].get_or_create<sol::table>();
			spriteTable.set_function("SetColor", &LuaEntity::SetColor, &scriptComponent.ScriptEntity);
			spriteTable.set_function("SetColorHSV", &LuaEntity::SetColorHSV, &scriptComponent.ScriptEntity);

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
		if (maybe_exception) {
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
