#include "cbpch.h"

#include "Cobalt/Scene/ECS/Entity.h"
#include "Cobalt/Scene/ECS/Components.h"

namespace Cobalt
{
	Entity::Entity(entt::entity handle, Scene* scene) : m_EntityHandle(handle), m_Scene(scene) { }

	UUID Entity::GetUUID()
	{
		return GetComponent<IDComponent>().UUID;
	}
	
	String Entity::GetName()
	{
		return GetComponent<TagComponent>().Name;
	}
}