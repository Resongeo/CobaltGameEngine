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

		entt::registry& Registry() { return m_Registry; }
		Entity CreateEntity(const std::string& name = "Entity");
		Entity CreateEntity(uint64_t id, const std::string& name = "Entity");

		std::string& GetName() { return m_Name; }
		void SetName(const char* name) { m_Name = std::string(name); }

		void ClearEntites();

	private:
		entt::registry m_Registry;
		std::string m_Name;

		friend class Entity;
	};
}