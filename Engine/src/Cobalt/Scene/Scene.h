#pragma once

#include "Cobalt/Scene/ECS/Components.h"
#include "Cobalt/Renderer/RenderCommand.h"

#include <entt.hpp>

namespace Cobalt
{
	class Entity;

	class Scene
	{
	public:
		Scene(const char* name = "Scene");

		void Update(float deltaTime);

		Entity CreateEntity(const std::string& name = "Entity");

		void DestroyEntity(Entity entity);
		void ClearEntites();

		std::string& GetName() { return m_Name; }
		void SetName(const char* name) { m_Name = std::string(name); }

		entt::registry& Registry() { return m_Registry; }

	private:
		entt::registry m_Registry;
		std::string m_Name;

		friend class Entity;
	};
}