#include "Scene/Scene.h"

#include "Scene/ECS/Entity.h"

namespace Cobalt
{
	Scene::Scene() { }

	void Scene::Update(float deltaTime)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto& transform = group.get<TransformComponent>(entity);
			auto& spriteRenderer = group.get<SpriteRendererComponent>(entity);

			RenderCommand::DrawQuad(transform.GetTransform(), spriteRenderer.Color, spriteRenderer.Tiling, spriteRenderer.Sprite);
		}
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TagComponent>(name);
		entity.AddComponent<TransformComponent>();
		return entity;
	}
}