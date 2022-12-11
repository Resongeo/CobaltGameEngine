#pragma once

#include "Cobalt.h"
using namespace Cobalt;

#include "Editor/Panels/Log/LogPanel.h"
#include "Editor/Panels/Scene/SceneHierarchyPanel.h"

struct EditorFonts
{
	ImFont* Regular;
	ImFont* SemiBold;
};

class EditorLayer : public Layer
{
public:
	EditorLayer();

	void OnAttach() override;
	void OnUpdate() override;
	void OnImGuiUpdate() override;

	Ref<Scene> GetActiveScene() const { return m_ActiveScene; }

	EditorFonts GetEditoFonts() const { return m_EditorFonts; }

private:
	Window m_Window;

	Scope<LogPanel> m_LogPanel;
	Scope<SceneHierarchyPanel> m_SceneHierarchyPanel;

	Ref<Texture> m_Texture;
	Ref<Framebuffer> m_Framebuffer;

	Ref<Scene> m_ActiveScene;

	SceneCamera m_SceneCamera;
	
	EditorFonts m_EditorFonts;

	struct SceneCameraData
	{
		glm::vec3 Position;
		float Rotation;
		float Size;
		float FOV;
	};
	SceneCameraData m_SceneCameraData;

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

	bool m_CameraSettingsOpened = false;
	bool m_GridSettingsOpened = false;

	bool m_Vsync = true;
	bool m_ShowFps = true;
};
