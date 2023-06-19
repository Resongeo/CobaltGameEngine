#pragma once

#include "Cobalt/Scene/ECS/Entity.h"

namespace Cobalt
{
	class ScriptEngine
	{
	public:
		static void RuntimeStart(Scene* scene);
		static void UpdateScripts(Scene* scene);

	private:
		static int ExceptionHandler(lua_State* L, sol::optional<const std::exception&> maybe_exception, sol::string_view description);
	};
}