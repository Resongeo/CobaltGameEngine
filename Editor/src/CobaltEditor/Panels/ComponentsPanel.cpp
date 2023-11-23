#include "pch.h"
#include "CobaltEditor/Managers/EditorPanelManager.h"
#include "CobaltEditor/Panels/ComponentsPanel.h"
#include "CobaltEditor/Panels/SceneHierarchyPanel.h"

namespace CobaltEditor
{
	void ComponentsPanel::OnLoad()
	{

	}

	void ComponentsPanel::OnUpdate()
	{
		m_SelectedEntity = SceneHierarchyPanel::GetSelectedEntity();
	}

	void ComponentsPanel::OnUIRender()
	{
		ImGui::Begin("Components");

		if (m_SelectedEntity)
		{
			DrawEntityComponents();
		}

		ImGui::End();

	}

	inline void ComponentsPanel::DrawEntityComponents()
	{
		ImGui::Text(m_SelectedEntity.GetComponent<TagComponent>().Tag.c_str());
		ImGui::Dummy({ 0, 10 });

		ImGuiTreeNodeFlags componentHeaderFlags = ImGuiTreeNodeFlags_DefaultOpen;

		if (m_SelectedEntity.HasComponent<TransformComponent>())
		{
			if (ImGui::CollapsingHeader("Transform", componentHeaderFlags))
			{
				auto& transform = m_SelectedEntity.GetComponent<TransformComponent>();
				ImGui::DragFloat3("Position", glm::value_ptr(transform.Position), 0.1f);
				ImGui::DragFloat3("Rotation", glm::value_ptr(transform.Rotation), 0.1f);
				ImGui::DragFloat3("Scale", glm::value_ptr(transform.Scale), 0.1f);
			}
		}

		if (m_SelectedEntity.HasComponent<SpriteRendererComponent>())
		{
			if (ImGui::CollapsingHeader("Sprite Renderer", componentHeaderFlags))
			{
				auto& spriteRenderer = m_SelectedEntity.GetComponent<SpriteRendererComponent>();
				ImGui::Image((ImTextureID)spriteRenderer.Texture->GetID(), { 40, 40 });
				ImGui::SameLine();
				ImGui::Text(spriteRenderer.Texture->GetPath().c_str());
				ImGui::ColorEdit4("Tint", spriteRenderer.Tint);
			}
		}
	}

	Ref<ComponentsPanel> ComponentsPanel::Create()
	{
		auto panel = CreateRef<ComponentsPanel>();
		EditorPanelManager::PushPanel(panel);

		return panel;
	}
}