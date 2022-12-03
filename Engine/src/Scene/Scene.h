#pragma once

#include "Scene/ECS/Components.h"

#include "Renderer/RenderCommand.h"

#include <entt.hpp>

namespace Cobalt
{
	class Entity;

	class Scene
	{
	public:
		Scene();

		void Update(float deltaTime);

		entt::registry& Reg() { return m_Registry; }
		Entity CreateEntity(const std::string& name = "Entity");

	private:
		entt::registry m_Registry;

		friend class Entity;
	};
}