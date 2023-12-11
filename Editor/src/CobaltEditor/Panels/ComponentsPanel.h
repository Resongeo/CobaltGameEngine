#pragma once

#include "CobaltEditor/Panels/EditorPanel.h"

namespace CobaltEditor
{
	struct ComponentProperties
	{
		const char* Title = "";
		Color PrimaryColor;
		bool Opened = true;
	};

	class ComponentsPanel : public EditorPanel
	{
	public:
		ComponentsPanel() = default;

		void OnLoad() override;
		void OnUpdate() override;
		void OnUIRender() override;

		static Ref<ComponentsPanel> Create();

	private:
		inline void DrawEntityComponents();
		inline void DrawAddComponentPopup();

	private:
		Entity m_SelectedEntity = {};
		ComponentProperties m_TransformProps;
		ComponentProperties m_SpriteRendererProps;
	};
}