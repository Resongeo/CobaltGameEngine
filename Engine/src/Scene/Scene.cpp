#include "Scene/Scene.h"

namespace Cobalt
{
	Scene::Scene()
	{
	}

	void Scene::Update(float deltaTime)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto& transform = group.get<TransformComponent>(entity);
			auto& spriteRenderer = group.get<SpriteRendererComponent>(entity);

			RenderCommand::DrawQuad(transform, spriteRenderer.Color, spriteRenderer.Sprite);
		}
	}

	entt::entity Scene::CreateEntity()
	{
		return m_Registry.create();
	}
}