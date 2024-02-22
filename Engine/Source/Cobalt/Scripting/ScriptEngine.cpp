#include "cbpch.h"
#include "Cobalt/Scripting/ScriptClass.h"
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
	}

	struct ScriptEngineData
	{
		MonoDomain* RootDomain = nullptr;
		MonoDomain* AppDomain = nullptr;
		MonoAssembly* CoreAssembly = nullptr;
		MonoImage* CoreAssemblyImage = nullptr;

		HashMap<String, Unique<ScriptClass>> EntityClasses;
	};
	static ScriptEngineData s_Data;

	void ScriptEngine::Init()
	{
		InitMono();
		LoadCoreAssembly();
		GetEntityClasses(s_Data.CoreAssemblyImage);
		ScriptFunctionRegistry::RegisterFunctions();
	}

	void ScriptEngine::InstantiateEntity(const String& className, u32 entityID)
	{
		s_Data.EntityClasses[className]->InvokeConstructor(entityID);
		s_Data.EntityClasses[className]->InvokeOnCreate();
	}

	void ScriptEngine::UpdateEntity(const String& className)
	{
		s_Data.EntityClasses[className]->InvokeOnUpdate();
	}

	bool ScriptEngine::IsEntityClassExists(const String& className)
	{
		return s_Data.EntityClasses.find(className) != s_Data.EntityClasses.end();
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

		s_Data.CoreAssemblyImage = mono_assembly_get_image(s_Data.CoreAssembly);
	}

	void ScriptEngine::GetEntityClasses(MonoImage* image)
	{
		s_Data.EntityClasses.clear();

		const MonoTableInfo* typeDefinitionsTable = mono_image_get_table_info(image, MONO_TABLE_TYPEDEF);
		size numTypes = mono_table_info_get_rows(typeDefinitionsTable);

		for (size i = 0; i < numTypes; i++)
		{
			u32 cols[MONO_TYPEDEF_SIZE];
			mono_metadata_decode_row(typeDefinitionsTable, i, cols, MONO_TYPEDEF_SIZE);

			const char* nameSpace = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAMESPACE]);
			const char* name = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAME]);

			auto monoClass = mono_class_from_name(image, nameSpace, name);
			auto entityClass = mono_class_from_name(image, "Cobalt", "Entity");

			if (entityClass == nullptr)
				continue;

			if (monoClass == entityClass)
				continue;

			bool isEntity = mono_class_is_subclass_of(monoClass, entityClass, false);
			if (isEntity)
			{
				String fullname = std::format("{}.{}", nameSpace, name);
				s_Data.EntityClasses[fullname] = CreateUnique<ScriptClass>(s_Data.CoreAssembly, s_Data.AppDomain, nameSpace, name);
			}

			LOG_TRACE("{}.{}", nameSpace, name);
		}
	}
}