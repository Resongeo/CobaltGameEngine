#pragma once

#include "Cobalt/Scene/Scene.h"
#include "Cobalt/Scene/Serialization/SceneSerializer.h"

namespace Cobalt
{
	class SceneManager
	{
	public:
		static Ref<Scene> GetActiveScene() { return s_Instance->m_ActiveScene; }
		static void CreateDefaultScene();
		static void LoadScene(const char* name);

		static void AddScenePath(const char* sceneName, const char* filepath);

	private:
		static void Init();
		
		friend class Application;

	private:
		static SceneManager* s_Instance;
		static SceneSerializer s_SceneSerializer;

		Ref<Scene> m_ActiveScene;
		std::unordered_map<std::string, std::string> m_ScenePaths;
	};
}