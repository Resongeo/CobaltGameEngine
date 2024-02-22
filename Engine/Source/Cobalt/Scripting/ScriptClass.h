#pragma once

#include "Cobalt/Core/Types.h"
#include "Cobalt/Scripting/Fwd.h"

namespace Cobalt
{
	class ScriptClass
	{
	public:
		ScriptClass(MonoAssembly* assembly, MonoDomain* domain, const String& namespaceName, const String& className);

		void InvokeConstructor(u32 entityID);
		void InvokeOnCreate();
		void InvokeOnUpdate();

		static Unique<ScriptClass> Create(MonoAssembly* assembly, MonoDomain* domain, const String& namespaceName, const String& className);

	private:
		MonoClass* m_MonoClass = nullptr;
		MonoObject* m_MonoObject = nullptr;
		MonoMethod* m_Constructor = nullptr;
		MonoMethod* m_OnCreateMethod = nullptr;
		MonoMethod* m_OnUpdateMethod = nullptr;
	};
}