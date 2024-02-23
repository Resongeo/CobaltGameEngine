#pragma once

#include "Cobalt/Core/Types.h"
#include "Cobalt/Scene/SceneState.h"

#include <entt.hpp>

namespace Cobalt
{
	class Entity;

	class Scene
	{
	public:
		Scene(const String& name = "Scene");

		Entity CreateEntity(const String& name = "Entity");
		Entity CreateEntityWithUUID(UUID uuid, const String& name = "Entity");

		void RuntimeStart();
		void EditorUpdate();
		void RuntimeUpdate();

		void DestroyEntity(Entity entity);
		void ClearEntites();

		String& GetName() { return m_Name; }
		SceneState GetState() const { return m_State; }

		void SetName(const char* name) { m_Name = String(name); }
		void SetState(SceneState state) { m_State = state; }

		static Shared<Scene> Copy(const Shared<Scene>& other);
		entt::registry& Registry() { return m_Registry; }

		static Shared<Scene> Create(const String& name);

	private:
		void RenderScene();

	private:
		entt::registry m_Registry;
		String m_Name;
		SceneState m_State = SceneState::None;
		HashMap<UUID, entt::entity> m_Entites;
		HashMap<String, entt::entity> m_EntityNames;

		friend class Entity;
	};
}