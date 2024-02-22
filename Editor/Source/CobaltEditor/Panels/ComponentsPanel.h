#pragma once

#include "CobaltEditor/Components/ContextPopup.h"
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

		static Shared<ComponentsPanel> Create();

	private:
		inline void DrawEntityComponents();


	private:
		Entity m_SelectedEntity = {};
		ComponentProperties m_TransformProps;
		ComponentProperties m_ScriptProps;
		ComponentProperties m_SpriteRendererProps;
		ContextPopup m_ContextPopup;
	};
}