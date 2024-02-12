#pragma once

#include "Cobalt/Core/Types.h"
#include "Cobalt/Scene/Scene.h"

#include <entt.hpp>

namespace Cobalt
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity&) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			return m_Scene->Registry().emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->Registry().all_of<T>(m_EntityHandle);
		}

		template<typename T>
		T& GetComponent()
		{
			return m_Scene->Registry().get<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			m_Scene->Registry().remove<T>(m_EntityHandle);
		}

		operator bool() const { return (uint32_t)m_EntityHandle != entt::null; }
		operator uint32_t() const { return (uint32_t)m_EntityHandle; }
		operator entt::entity() const { return m_EntityHandle; }

		bool operator ==(const Entity& otherEntity) const
		{
			return m_EntityHandle == otherEntity.m_EntityHandle && m_Scene == otherEntity.m_Scene;
		}
		bool operator !=(const Entity& otherEntity) const
		{
			return m_EntityHandle != otherEntity.m_EntityHandle || m_Scene != otherEntity.m_Scene;
		}

		void Test() const;

	private:
		entt::entity m_EntityHandle{ entt::null };
		Scene* m_Scene = nullptr;
	};
}