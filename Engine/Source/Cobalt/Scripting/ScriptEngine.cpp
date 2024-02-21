#include "cbpch.h"
#include "Cobalt/Scripting/ScriptEngine.h"

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
			MonoImage* image = mono_image_open_from_data_full(buffer.As<char>(), buffer.Size, 1, &status, 0);

			if (status != MONO_IMAGE_OK)
			{
				const char* errorMessage = mono_image_strerror(status);
				LOG_ERROR("Mono error: {}", errorMessage);
				return nullptr;
			}

			MonoAssembly* assembly = mono_assembly_load_from_full(image, assemblyPath.c_str(), &status, 0);

			mono_image_close(image);
			buffer.Release();

			return assembly;
		}

		static MonoClass* GetClassInAssembly(MonoAssembly* assembly, const char* namespaceName, const char* className)
		{
			MonoImage* image = mono_assembly_get_image(assembly);
			MonoClass* result = mono_class_from_name(image, namespaceName, className);

			if (result == nullptr)
			{
				LOG_ERROR("Failed to get class: {}.{}", namespaceName, className);
				return nullptr;
			}

			return result;
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
		mono_set_assemblies_path("Mono/lib");

		s_Data.RootDomain = mono_jit_init("Cobalt-JIT-Runtime");
		if (s_Data.RootDomain == nullptr)
		{
			LOG_ERROR("Failed to initialize Mono JIT");
			return;
		}
		LOG_INFO("Initialized Mono JIT");

		s_Data.AppDomain = mono_domain_create_appdomain((char*)"Cobalt-Runtime", nullptr);
		mono_domain_set(s_Data.AppDomain, true);

		s_Data.CoreAssembly = Utils::LoadAssembly("Resources/Cobalt-ScriptCore.dll");
		if (s_Data.CoreAssembly == nullptr)
		{
			LOG_ERROR("Failed to load Cobalt-ScriptCore.dll");
			return;
		}
		LOG_INFO("Loaded Cobalt-ScriptCore.dll");

		auto mainClass = Utils::GetClassInAssembly(s_Data.CoreAssembly, "Cobalt", "Main");
		auto mainInstance = mono_object_new(s_Data.AppDomain, mainClass);
		mono_runtime_object_init(mainInstance);
	}

	void ScriptEngine::PrintAssemblyTypes(MonoAssembly* assembly)
	{
		MonoImage* image = mono_assembly_get_image(assembly);
		const MonoTableInfo* typeDefinitionsTable = mono_image_get_table_info(image, MONO_TABLE_TYPEDEF);
		size numTypes = mono_table_info_get_rows(typeDefinitionsTable);

		for (size i = 0; i < numTypes; i++)
		{
			u32 cols[MONO_TYPEDEF_SIZE];
			mono_metadata_decode_row(typeDefinitionsTable, i, cols, MONO_TYPEDEF_SIZE);

			const char* nameSpace = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAMESPACE]);
			const char* name = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAME]);

			LOG_TRACE("{}.{}", nameSpace, name);
		}
	}
}