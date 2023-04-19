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
		Scene();

		void Update(float deltaTime);

		entt::registry& Registry() { return m_Registry; }
		Entity CreateEntity(const std::string& name = "Entity");

	private:
		entt::registry m_Registry;

		friend class Entity;
	};
}