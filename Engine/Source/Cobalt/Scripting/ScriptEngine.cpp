#include "cbpch.h"
#include "Cobalt/Scripting/ScriptEngine.h"
#include "Cobalt/Scripting/ScriptFunctionRegistry.h"

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

namespace Cobalt
{
	namespace Utils
	{
		static MonoAssembly* LoadAssembly(const String& assemblyPath)
		{
			auto buffer = Buffer::FromFile(assemblyPath);

			MonoImageOpenStatus status;
			auto image = mono_image_open_from_data_full(buffer.As<char>(), buffer.Size, 1, &status, 0);

			if (status != MONO_IMAGE_OK)
			{
				const char* errorMessage = mono_image_strerror(status);
				LOG_ERROR("Mono error: {}", errorMessage);
				return nullptr;
			}

			auto assembly = mono_assembly_load_from_full(image, assemblyPath.c_str(), &status, 0);

			mono_image_close(image);
			buffer.Release();

			return assembly;
		}

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

		static MonoObject* InstantiateClass(MonoAssembly* assembly, MonoDomain* domain, const char* namespaceName, const char* className)
		{
			auto classInstance = Utils::GetClassInAssembly(assembly, namespaceName, className);

			auto classObject = mono_object_new(domain, classInstance);
			if (classObject == nullptr)
			{
				LOG_ERROR("Failed to allocate {}.{}", namespaceName, className);
				return nullptr;
			}

			mono_runtime_object_init(classObject);

			return classObject;
		}
	}

	struct ScriptEngineData
	{
		MonoDomain* RootDomain = nullptr;
		MonoDomain* AppDomain = nullptr;
		MonoAssembly* CoreAssembly = nullptr;
	};
	static ScriptEngineData s_Data;

	void ScriptEngine::Init()
	{
		InitMono();
		LoadCoreAssembly();
		ScriptFunctionRegistry::RegisterFunctions();

		Utils::InstantiateClass(s_Data.CoreAssembly, s_Data.AppDomain, "Cobalt", "Main");
	}

	void ScriptEngine::InitMono()
	{
		mono_set_assemblies_path("Mono/lib");

		s_Data.RootDomain = mono_jit_init("Cobalt-JIT-Runtime");
		if (s_Data.RootDomain == nullptr)
		{
			LOG_ERROR("Failed to initialize Mono JIT");
			return;
		}
		LOG_INFO("Initialized Mono JIT");
	}

	void ScriptEngine::LoadCoreAssembly()
	{
		s_Data.AppDomain = mono_domain_create_appdomain((char*)"Cobalt-Runtime", nullptr);
		mono_domain_set(s_Data.AppDomain, true);

		s_Data.CoreAssembly = Utils::LoadAssembly("Resources/Cobalt-ScriptCore.dll");
		if (s_Data.CoreAssembly == nullptr)
		{
			LOG_ERROR("Failed to load Cobalt-ScriptCore.dll");
			return;
		}
		LOG_INFO("Loaded Cobalt-ScriptCore.dll");
	}
}