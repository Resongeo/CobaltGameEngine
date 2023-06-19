#pragma once

#include "Cobalt.h"
using namespace Cobalt;

#include "Editor/Panels/Log/LogPanel.h"
#include "Editor/Panels/Assets/AssetBrowserPanel.h"
#include "Editor/Panels/Profiler/ProfilerPanel.h"
#include "Editor/Panels/Profiler/RenderStatisticsPanel.h"
#include "Editor/Panels/Scene/SceneHierarchyPanel.h"
#include "Editor/Panels/Components/ComponentsPanel.h"
#include "Editor/Panels/EditorPanelManager.h"
#include "Editor/Panels/Viewport/ViewportPanel.h"
#include "Editor/Style/StyleManager.h"
#include "Editor/Utils/Controls.h"


class EditorLayer : public Layer
{
public:
	EditorLayer();

	void OnAttach() override;
	void OnUpdate() override;
	void OnImGuiUpdate() override;
	void OnEvent(Event& event) override;

	Ref<Scene> GetActiveScene() const { return m_ActiveScene; }
	SceneState SceneState = SceneState::Edit;

private:
	Ref<Window> m_Window;
	Ref<Framebuffer> m_Framebuffer;
	Ref<Scene> m_ActiveScene;

	Scope<LogPanel> m_LogPanel;
	Scope<AssetBrowserPanel> m_AssetBrowserPanel;
	Scope<ProfilerPanel> m_ProfilerPanel;
	Scope<RenderStatisticsPanel> m_RenderStatisticsPanel;
	Scope<ComponentsPanel> m_ComponentsPanel;
	Scope<ViewportPanel> m_ViewportPanel;
	Ref<SceneHierarchyPanel> m_SceneHierarchyPanel;


	EditorCamera m_EditorCamera;
	Camera* m_ActiveCamera;

	EditorFonts* m_EditorFonts;

	struct GridData
	{
		int Size;
		float GapSize;
		float LineWidth;
	};
	GridData m_GridData;

	Vec4 m_ClearColor { 0.09f, 0.09f, 0.1f, 1.0f };
	Vec4 m_GridColor{ 0.17f, 0.17f, 0.17f, 1.0f };
};
