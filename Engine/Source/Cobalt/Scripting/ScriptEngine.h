#pragma once

#include "Cobalt/Scripting/Fwd.h"

namespace Cobalt
{
	class ScriptEngine
	{
	public:
		static void Init();

	private:
		static void PrintAssemblyTypes(MonoAssembly* assembly);
	};
}