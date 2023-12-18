#include "pch.h"
#include "CobaltEditor/Managers/EditorPanelManager.h"
#include "CobaltEditor/Panels/ComponentsPanel.h"
#include "CobaltEditor/Panels/SceneHierarchyPanel.h"

namespace CobaltEditor
{
	static std::unordered_map<const char*, float> s_ComponentHeight;
	static Color s_BackgroundCol;
	static Color s_InactiveCol;

	void ComponentsPanel::OnLoad()
	{
		auto& colors = StyleManager::GetColors();
		s_BackgroundCol = colors.Panels.Components.BackgroundColor;
		s_InactiveCol = colors.Panels.Components.InactiveColor;

		m_TransformProps.Title = "Transform";
		m_TransformProps.PrimaryColor = colors.Panels.Components.TransformColor;

		m_SpriteRendererProps.Title = "Sprite Renderer";
		m_SpriteRendererProps.PrimaryColor = colors.Panels.Components.SpriteRendererColor;

		m_ContextPopup.SetTitle("Add Component");
		m_ContextPopup.AddMenuItem("Transform", []()
		{
			SceneHierarchyPanel::GetSelectedEntity().AddComponent<TransformComponent>();
		});
		m_ContextPopup.AddMenuItem("Sprite Renderer", []()
		{
			SceneHierarchyPanel::GetSelectedEntity().AddComponent<SpriteRendererComponent>();
		});
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
		else
		{
			m_ContextPopup.Close();
		}

		m_ContextPopup.Draw();
		ImGui::End();

	}

	template<typename T, typename Content>
	static void DrawComponent(Entity entity, ComponentProperties& props, Content content)
	{
		ImGuiTreeNodeFlags componentHeaderFlags = ImGuiTreeNodeFlags_DefaultOpen;

		if (entity.HasComponent<T>())
		{
			if (s_ComponentHeight.find(props.Title) == s_ComponentHeight.end())
			{
				s_ComponentHeight[props.Title] = 0.0f;
			}

			Color primaryColor = props.Opened ? props.PrimaryColor : s_InactiveCol;

			auto min = ImGui::GetCursorScreenPos();
			auto max = ImVec2(min.x + ImGui::GetContentRegionAvail().x, min.y + s_ComponentHeight[props.Title]);
			Shapes::DrawRectOutlined(min, max, s_BackgroundCol, primaryColor, 5.0f, 3.0f);

			ImGui::BeginGroup();
			{
				{
					ScopedFont _(StyleManager::GetFonts().SemiBold);
					CursorUtils::Translate({ 10, 7 });
					ImGui::TextColored(primaryColor, props.Title);
					CursorUtils::Translate({ 10, 7 });
				}

				max = { max.x, min.y + ImGui::CalcTextSize(props.Title).y + 16 };

				if (MouseUtils::Intersect(min, max) && Input::GetMouseButtonClicked(MOUSE_BUTTON_LEFT))
				{
					props.Opened = !props.Opened;
				}

				if (props.Opened)
				{
					content(entity.GetComponent<T>());
					ImGui::Dummy({ 0, 7 });
				}
			}
			ImGui::EndGroup();
			s_ComponentHeight[props.Title] = ImGui::GetItemRectSize().y;

			ImGui::Dummy({ 0, 10 });
		}
	}

	inline void ComponentsPanel::DrawEntityComponents()
	{
		{
			ScopedFont _(StyleManager::GetFonts().SemiBold);
			CursorUtils::Translate({ 5, 3 });
			ImGui::Text(m_SelectedEntity.GetComponent<TagComponent>().Tag.c_str());
		}

		ImGui::SameLine();
		const char* btnText = ICON_FA_PLUS " Add";
		Vec2 btnPadding = { 25, 8 };
		auto btnTextSize = ImGui::CalcTextSize(btnText);
		CursorUtils::Translate({ ImGui::GetContentRegionAvail().x - btnTextSize.x - (btnPadding.x + 5.0f), -btnPadding.y / 2.0f});
		{
			ScopedColor _(ImGuiCol_Button, Color(38));
			if (ImGui::Button(btnText, { btnTextSize.x + btnPadding.x, btnTextSize.y + btnPadding.y }))
			{
				m_ContextPopup.Toggle();
			}
		}

		ImGui::Dummy({ 0, 10 });

		DrawComponent<TransformComponent>(m_SelectedEntity, m_TransformProps, [](auto& component)
		{
			Controls::Vector3("Position", component.Position, 0.0f, 0.1f, 100.0f, -1.0f, { 10, 0 }, 8.0f);
			Controls::Vector3("Rotaiton", component.Rotation, 0.0f, 0.1f, 100.0f, -1.0f, { 10, 0 }, 8.0f);
			Controls::Vector3("Scale", component.Scale, 1.0f, 0.1f, 100.0f, -1.0f, { 10, 0 }, 8.0f);
		});

		DrawComponent<SpriteRendererComponent>(m_SelectedEntity, m_SpriteRendererProps, [](auto& component)
		{
			ImGui::Image((ImTextureID)component.Texture->GetID(), { 40, 40 });
			ImGui::SameLine();
			ImGui::Text(component.Texture->GetPath().c_str());
			ImGui::ColorEdit4("Tint", component.Tint);
		});
	}

	Ref<ComponentsPanel> ComponentsPanel::Create()
	{
		auto panel = CreateRef<ComponentsPanel>();
		EditorPanelManager::PushPanel(panel);

		return panel;
	}
}