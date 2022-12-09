#pragma once

#include "Core/Core.h"
#include "Scene/Scene.h"

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
			return m_Scene->Reg().emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->Reg().has<T>(m_EntityHandle);
		}

		template<typename T>
		T& GetComponent()
		{
			return m_Scene->Reg().get<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			m_Scene->Reg().remove<T>(m_EntityHandle);
		}

		operator bool() const { return (uint32_t)m_EntityHandle != 0; }

	private:
		entt::entity m_EntityHandle{ 0 };
		Scene* m_Scene = nullptr;
	};
}