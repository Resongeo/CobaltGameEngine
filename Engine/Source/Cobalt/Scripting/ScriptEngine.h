#pragma once

#include "Cobalt/Core/Types.h"
#include "Cobalt/Scripting/Fwd.h"

namespace Cobalt
{
	class ScriptEngine
	{
	public:
		static void Init();

		static void InstantiateEntity(const String& className, u32 entityID);
		static void UpdateEntity(const String& className);
		static bool IsEntityClassExists(const String& className);

	private:
		static void InitMono();
		static void LoadCoreAssembly();
		static void GetEntityClasses(MonoImage* image);
	};
}