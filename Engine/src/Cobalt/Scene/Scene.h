#pragma once

#include "Cobalt/Rendering/RenderCommand.h"
#include "Cobalt/Scene/SceneState.h"
#include "Cobalt/Scene/ECS/Components.h"

#include <entt.hpp>

namespace Cobalt
{
	class Entity;

	class Scene
	{
	public:
		Scene(const char* name = "Scene");

		void RuntimeStart();

		void EditorUpdate();
		void RuntimeUpdate();

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