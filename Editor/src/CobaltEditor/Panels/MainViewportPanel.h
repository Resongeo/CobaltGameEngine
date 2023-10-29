#pragma once

#include "CobaltEditor/Panels/EditorPanel.h"
#include "CobaltEditor/Components/Viewport.h"

namespace CobaltEditor
{
	class MainViewportPanel : public EditorPanel
	{
	public:
		MainViewportPanel(const Ref<Scene>& scene);

		void Update() override;
		void UIRender() override;

		static Ref<MainViewportPanel> Create(const Ref<Scene>& scene);

	private:
		Ref<Scene> m_Scene;
		Ref<Viewport> m_Viewport;
		Ref<EditorCamera> m_EditorCamera;

		Vec2 m_ViewportBounds[2] = {};
		ImVec2 m_ViewportSize;
	};
}