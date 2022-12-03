#pragma once

#include "Scene/Components.h"
#include "Renderer/RenderCommand.h"

#include <entt.hpp>

namespace Cobalt
{
	class Scene
	{
	public:
		Scene();

		void Update(float deltaTime);

		entt::registry& Reg() { return m_Registry; }
		entt::entity CreateEntity();

	private:
		entt::registry m_Registry;
	};
}