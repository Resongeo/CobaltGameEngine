#include "Scene/ECS/Entity.h"

namespace Cobalt
{
	Entity::Entity(entt::entity handle, Scene* scene) : m_EntityHandle(handle), m_Scene(scene)
	{

	}
}