#include "cbpch.h"

#include "Cobalt/Scene/SceneManager.h"
#include "Cobalt/Scene/ECS/Entity.h"

namespace Cobalt
{
	SceneManager* SceneManager::s_Instance = nullptr;
	SceneSerializer SceneManager::s_SceneSerializer;

	void SceneManager::LoadScene(const char* name)
	{
		s_SceneSerializer.Deserialize(s_Instance->m_ScenePaths[name], s_Instance->m_ActiveScene);
	}

	Shared<Scene> SceneManager::CreateDefaultScene()
	{
		s_Instance->m_ActiveScene = Scene::Create("Default Scene");
		auto entity = s_Instance->m_ActiveScene->CreateEntity("Square");
		entity.AddComponent<SpriteRendererComponent>().Tint = Color(230, 80, 80);
		entity.AddComponent<ScriptComponent>().ClassName = "Test.Player";

		return s_Instance->m_ActiveScene;
	}

	void SceneManager::Init()
	{
		s_Instance = new SceneManager();
	}

	void SceneManager::AddScenePath(const char* sceneName, const char* filepath)
	{
		if (s_Instance->m_ScenePaths.find(sceneName) != s_Instance->m_ScenePaths.end()) return;

		s_Instance->m_ScenePaths[sceneName] = filepath;
	}
}