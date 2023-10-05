#include "cbpch.h"

#include "Cobalt/Scene/ECS/Entity.h"
#include "Cobalt/Logger/Log.h"

namespace Cobalt
{
	Entity::Entity(entt::entity handle, Scene* scene) : m_EntityHandle(handle), m_Scene(scene) { }

	void Entity::Test()
	{
		LOG_WARN("Entity ID: {0}", (uint32_t)m_EntityHandle);
	}
}