#include "cbpch.h"

#include "Cobalt/Scene/Scene.h"
#include "Cobalt/Scene/ECS/Entity.h"

namespace Cobalt
{
	Scene::Scene(const char* name)
	{
		m_Name = std::string(name);
		m_Registry.clear();
	}

	void Scene::Update(float deltaTime)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto& transform = group.get<TransformComponent>(entity);
			auto& spriteRenderer = group.get<SpriteRendererComponent>(entity);

			RenderCommand::DrawSprite(transform.GetTransform(), spriteRenderer);
		}
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TagComponent>(name);
		entity.AddComponent<TransformComponent>();
		return entity;
	}

	void Scene::ClearEntites()
	{
		m_Registry.each([&](auto entityID)
		{
			m_Registry.destroy(entityID);
		});
	}
}