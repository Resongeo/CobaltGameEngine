#include "cbpch.h"

#include "Cobalt/Scene/ECS/Entity.h"

namespace Cobalt
{
	Entity::Entity(entt::entity handle, Scene* scene) : m_EntityHandle(handle), m_Scene(scene) { }

	void Entity::Test() const
	{
		LOG_WARN("Entity ID: {0}", (u32)m_EntityHandle);
	}
}