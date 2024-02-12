#pragma once

#include "Cobalt/Core/Types/String.h"
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

		Entity CreateEntity(const String& name = "Entity");
		void DestroyEntity(Entity entity);
		void ClearEntites();

		String& GetName() { return m_Name; }
		void SetName(const char* name) { m_Name = String(name); }

		entt::registry& Registry() { return m_Registry; }

		static Shared<Scene> Create(const char* name);

	private:
		entt::registry m_Registry;
		String m_Name;

		friend class Entity;
	};
}