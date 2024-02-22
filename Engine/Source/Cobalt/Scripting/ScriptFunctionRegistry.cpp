#include "cbpch.h"
#include "Cobalt/Scripting/ScriptFunctionRegistry.h"
#include "Cobalt/Input/Input.h"
#include "Cobalt/Scene/SceneManager.h"
#include "Cobalt/Scene/ECS/Entity.h"

#include <mono/jit/jit.h>

namespace Cobalt
{
#define ADD_MONO_INTERNAL_CALL(name) mono_add_internal_call("Cobalt.InternalCalls::" #name, name)

#pragma region Log

	static void EngineLog_Trace(MonoString* string)
	{
		char* message = mono_string_to_utf8(string);
		LOG_TRACE("{}", message);
		mono_free(message);
	}
	static void EngineLog_Info(MonoString* string)
	{
		char* message = mono_string_to_utf8(string);
		LOG_INFO("{}", message);
		mono_free(message);
	}
	static void EngineLog_Warn(MonoString* string)
	{
		char* message = mono_string_to_utf8(string);
		LOG_WARN("{}", message);
		mono_free(message);
	}
	static void EngineLog_Error(MonoString* string)
	{
		char* message = mono_string_to_utf8(string);
		LOG_ERROR("{}", message);
		mono_free(message);
	}

#pragma endregion

#pragma region Input

	static bool Input_GetKeyDown(int keycode)
	{
		return Input::GetKeyDown(keycode);
	}

#pragma endregion

#pragma region Transform

	static void Transform_Translate(u64 entityID, Vec3 translation)
	{
		auto scene = SceneManager::GetActiveScene();
		Entity entity = { (entt::entity)entityID, scene.get() };

		auto& transform = entity.GetComponent<TransformComponent>();
		transform.Position += translation;
	}

#pragma endregion

	void ScriptFunctionRegistry::RegisterFunctions()
	{
		ADD_MONO_INTERNAL_CALL(EngineLog_Trace);
		ADD_MONO_INTERNAL_CALL(EngineLog_Info);
		ADD_MONO_INTERNAL_CALL(EngineLog_Warn);
		ADD_MONO_INTERNAL_CALL(EngineLog_Error);

		ADD_MONO_INTERNAL_CALL(Input_GetKeyDown);

		ADD_MONO_INTERNAL_CALL(Transform_Translate);
	}
}