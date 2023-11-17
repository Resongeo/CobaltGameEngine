#pragma once

#include "CobaltEditor/Panels/EditorPanel.h"

namespace CobaltEditor
{
	class ComponentsPanel : public EditorPanel
	{
	public:
		ComponentsPanel() = default;

		void OnUpdate() override;
		void OnUIRender() override;

		static Ref<ComponentsPanel> Create();

	private:
		inline void DrawEntityComponents();

	private:
		Entity m_SelectedEntity = {};
	};
}