#pragma once

#include "Cobalt/Core/Types.h"
#include "Cobalt/Scene/Scene.h"
#include "Cobalt/Scene/Serialization/SceneSerializer.h"

namespace Cobalt
{
	class SceneManager
	{
	public:
		static void SetActiveScene(Shared<Scene> scene) { s_Instance->m_ActiveScene = scene; }
		static Shared<Scene> GetActiveScene() { return s_Instance->m_ActiveScene; }
		static Shared<Scene> CreateDefaultScene();
		static void LoadScene(const char* name);

		static void AddScenePath(const char* sceneName, const char* filepath);

	private:
		static void Init();
		
		friend class Application;

	private:
		static SceneManager* s_Instance;
		static SceneSerializer s_SceneSerializer;

		Shared<Scene> m_ActiveScene;
		HashMap<String, String> m_ScenePaths;
	};
}