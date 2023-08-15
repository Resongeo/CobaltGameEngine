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

	bool OnEngineTraceLog(LogTraceEvent& event);
	bool OnEngineInfoLog(LogInfoEvent& event);
	bool OnEngineWarnLog(LogWarnEvent& event);
	bool OnEngineErrorLog(LogErrorEvent& event);

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

	bool m_Vsync = true;

	struct GridData
	{
		int Size;
		float GapSize;
		float LineWidth;
	};
	GridData m_GridData;

	Color m_ClearColor = Color(23, 23, 25);
	Color m_GridColor = Color(43, 43, 43);
	Color m_BarColor = Color(20, 20, 21);

	float m_TopBarHeight = 50.0f;
	float m_SideBarWidth = 40.0f;
	float m_BottomBarHeight = 10.0f;
};
