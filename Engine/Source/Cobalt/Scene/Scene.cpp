#include "cbpch.h"

#include "Cobalt/Core/Random.h"
#include "Cobalt/Scene/Scene.h"
#include "Cobalt/Scene/ECS/Entity.h"
#include "Cobalt/Scene/ECS/Components.h"
#include "Cobalt/Scripting/ScriptEngine.h"
#include "Cobalt/Rendering/RenderCommand.h"

namespace Cobalt
{
	Scene::Scene(const String& name) : m_Name(name)
	{
		m_Registry.clear();
	}

	void Scene::RuntimeStart()
	{
		auto view = m_Registry.view<ScriptComponent>();
		for (auto entityID : view)
		{
			Entity entity = { entityID, this };
			auto& script = entity.GetComponent<ScriptComponent>();

			if (ScriptEngine::IsEntityClassExists(script.ClassName))
			{
				ScriptEngine::InstantiateEntity(script.ClassName, (u32)entityID);
			}
		}
	}

	void Scene::EditorUpdate()
	{
		RenderScene();
	}

	void Scene::RuntimeUpdate()
	{
		RenderScene();

		auto view = m_Registry.view<ScriptComponent>();
		for (auto entityID : view)
		{
			Entity entity = { entityID, this };
			auto& script = entity.GetComponent<ScriptComponent>();
			ScriptEngine::UpdateEntity(script.ClassName);
		}
	}

	Shared<Scene> Scene::Copy(const Shared<Scene>& other)
	{
		auto scene = Scene::Create(other->m_Name);
		scene->m_State = other->m_State;

		auto& sourceRegistry = other->m_Registry;
		auto& destinationRegistry = scene->m_Registry;

		auto view = sourceRegistry.view<IDComponent>();
		for (auto entityID : view)
		{
			Entity sourceEntity = { entityID, other.get() };
			auto& uuid = sourceEntity.GetComponent<IDComponent>().UUID;
			auto& name = sourceEntity.GetComponent<TagComponent>().Name;
			auto& transform = sourceEntity.GetComponent<TransformComponent>();

			Entity newEntity = scene->CreateEntityWithUUID(uuid, name);
			newEntity.GetComponent<TransformComponent>() = transform;

			if (sourceEntity.HasComponent<ScriptComponent>())
			{
				auto& component = sourceEntity.GetComponent<ScriptComponent>();
				newEntity.AddComponent<ScriptComponent>(component);
			}

			if (sourceEntity.HasComponent<SpriteRendererComponent>())
			{
				auto& component = sourceEntity.GetComponent<SpriteRendererComponent>();
				newEntity.AddComponent<SpriteRendererComponent>(component);
			}
		}

		return scene;
	}

	Entity Scene::CreateEntity(const String& name)
	{
		return CreateEntityWithUUID(Random::UUID(), name);
	}

	Entity Scene::CreateEntityWithUUID(UUID uuid, const String& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<IDComponent>(uuid);
		entity.AddComponent<TagComponent>(name);
		entity.AddComponent<TransformComponent>();

		m_Entites[uuid] = entity;
		m_EntityNames[name] = entity;

		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_Entites.erase(entity.GetUUID());
		m_EntityNames.erase(entity.GetName());
		m_Registry.destroy(entity);
	}

	void Scene::ClearEntites()
	{
		m_Registry.each([&](auto entityID)
		{
			m_Registry.destroy(entityID);
		});
	}

	Shared<Scene> Scene::Create(const String& name)
	{
		return CreateShared<Scene>(name);
	}

	void Scene::RenderScene()
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entityID : group)
		{
			Entity entity = { entityID, this };

			auto& transform = entity.GetComponent<TransformComponent>();
			auto& spriteRenderer = entity.GetComponent<SpriteRendererComponent>();

			RenderCommand::DrawEntity(transform.GetTransform(), spriteRenderer, entity);
		}
	}
}