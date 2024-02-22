#include "cbpch.h"
#include "Cobalt/Scripting/ScriptFunctionRegistry.h"

#include <mono/jit/jit.h>

namespace Cobalt
{
#define ADD_MONO_INTERNAL_CALL(name) mono_add_internal_call("Cobalt.InternalCalls::" #name, name)

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

	void ScriptFunctionRegistry::RegisterFunctions()
	{
		ADD_MONO_INTERNAL_CALL(EngineLog_Trace);
		ADD_MONO_INTERNAL_CALL(EngineLog_Info);
		ADD_MONO_INTERNAL_CALL(EngineLog_Warn);
		ADD_MONO_INTERNAL_CALL(EngineLog_Error);
	}
}