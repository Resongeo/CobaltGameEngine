#include "cbpch.h"

#include "Cobalt/Core/Random.h"
#include "Cobalt/Scene/Scene.h"
#include "Cobalt/Scene/ECS/Entity.h"

#include "Cobalt/Logger/Log.h"

namespace Cobalt
{
	Scene::Scene(const char* name)
	{
		m_Name = String(name);
		m_Registry.clear();
	}

	void Scene::RuntimeStart()
	{
		// TODO: Start script engine, physics etc...
	}

	void Scene::EditorUpdate()
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

	void Scene::RuntimeUpdate()
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entityID : group)
		{
			Entity entity = { entityID, this };

			auto& transform = entity.GetComponent<TransformComponent>();
			auto& spriteRenderer = entity.GetComponent<SpriteRendererComponent>();

			RenderCommand::DrawEntity(transform.GetTransform(), spriteRenderer, entity);
		}

		// TODO: Update script engine, physics etc...
	}

	Entity Scene::CreateEntity(const String& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<IDComponent>(Random::ID());
		entity.AddComponent<TagComponent>(name);
		entity.AddComponent<TransformComponent>();

		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}

	void Scene::ClearEntites()
	{
		m_Registry.each([&](auto entityID)
		{
			m_Registry.destroy(entityID);
		});
	}

	Shared<Scene> Scene::Create(const char* name)
	{
		return CreateShared<Scene>(name);
	}
}