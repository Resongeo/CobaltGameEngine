#include "cbpch.h"
#include "Cobalt/Scripting/ScriptClass.h"

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

namespace Cobalt
{
	namespace Utils
	{
		static MonoClass* GetClassInAssembly(MonoAssembly* assembly, const char* namespaceName, const char* className)
		{
			auto image = mono_assembly_get_image(assembly);
			auto result = mono_class_from_name(image, namespaceName, className);

			if (result == nullptr)
			{
				LOG_ERROR("Failed to get class: {}.{}", namespaceName, className);
				return nullptr;
			}

			return result;
		}

		static MonoObject* InstantiateClass(MonoClass* classInstance, MonoDomain* domain)
		{
			auto monoObject = mono_object_new(domain, classInstance);
			mono_runtime_object_init(monoObject);

			return monoObject;
		}

		static MonoMethod* GetMethodFromName(MonoClass* classInstance, const char* methodName, int paramCount)
		{
			return mono_class_get_method_from_name(classInstance, methodName, paramCount);
		}
	}

	ScriptClass::ScriptClass(MonoAssembly* assembly, MonoDomain* domain, const String& namespaceName, const String& className)
	{
		m_MonoClass = Utils::GetClassInAssembly(assembly, namespaceName.c_str(), className.c_str());
		m_MonoObject = Utils::InstantiateClass(m_MonoClass, domain);
		m_Constructor = Utils::GetMethodFromName(Utils::GetClassInAssembly(assembly, "Cobalt", "Entity"), ".ctor", 1);
		m_OnCreateMethod = Utils::GetMethodFromName(m_MonoClass, "OnCreate", 0);
		m_OnUpdateMethod = Utils::GetMethodFromName(m_MonoClass, "OnUpdate", 1);
	}

	void ScriptClass::InvokeConstructor(u32 entityID)
	{
		if (m_Constructor == nullptr || m_MonoObject == nullptr) return;

		void* params[] = {
			&entityID
		};

		mono_runtime_invoke(m_Constructor, m_MonoObject, params, nullptr);
	}

	void ScriptClass::InvokeOnCreate()
	{
		if (m_OnCreateMethod == nullptr || m_MonoObject == nullptr) return;
		mono_runtime_invoke(m_OnCreateMethod, m_MonoObject, nullptr, nullptr);
	}

	void ScriptClass::InvokeOnUpdate()
	{
		if (m_OnUpdateMethod == nullptr || m_MonoObject == nullptr) return;

		float dt = Time::deltaTime;

		void* params[] = {
			&dt
		};

		mono_runtime_invoke(m_OnUpdateMethod, m_MonoObject, params, nullptr);
	}

	Unique<ScriptClass> ScriptClass::Create(MonoAssembly* assembly, MonoDomain* domain, const String& namespaceName, const String& className)
	{
		return CreateUnique<ScriptClass>(assembly, domain, namespaceName, className);
	}
}