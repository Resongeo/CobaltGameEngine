#pragma once

#include "Cobalt.h"
using namespace Cobalt;

#include "Editor/Panels/Log/LogPanel.h"
#include "Editor/Panels/Profiler/ProfilerPanel.h"
#include "Editor/Panels/Profiler/RenderStatisticsPanel.h"
#include "Editor/Panels/Scene/SceneHierarchyPanel.h"
#include "Editor/Panels/Components/ComponentsPanel.h"

#include "Editor/Panels/EditorPanelManager.h"

#include "Editor/Style/StyleManager.h"


class EditorLayer : public Layer
{
public:
	EditorLayer();

	void OnAttach() override;
	void OnUpdate() override;
	void OnImGuiUpdate() override;
	void OnEvent(Event& event) override;

	Ref<Scene> GetActiveScene() const { return m_ActiveScene; }

private:
	Ref<Window> m_Window;

	Scope<LogPanel> m_LogPanel;
	Scope<ProfilerPanel> m_ProfilerPanel;
	Scope<RenderStatisticsPanel> m_RenderStatisticsPanel;
	Scope<ComponentsPanel> m_ComponentsPanel;
	Scope<SceneHierarchyPanel> m_SceneHierarchyPanel;

	Ref<Texture2D> m_Texture;
	Ref<Framebuffer> m_Framebuffer;

	Ref<Scene> m_ActiveScene;

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

	glm::vec4 m_ClearColor { 0.09f, 0.09f, 0.1f, 1.0f };
	glm::vec4 m_GridColor{ 0.17f, 0.17f, 0.17f, 1.0f };

	ImVec2 m_ViewportSize = { 0.0f, 0.0f };

	bool m_Vsync = true;
	bool m_ShowFps = true;
	bool m_ShowGrid = true;
};
