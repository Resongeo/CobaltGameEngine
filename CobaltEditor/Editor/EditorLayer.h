#pragma once

#include "Cobalt.h"
using namespace Cobalt;

class EditorLayer : public Layer
{
public:
	EditorLayer();

	void OnAttach() override;
	void OnUpdate(float deltaTime) override;
	void OnImGuiUpdate(float deltaTime) override;

private:
	Window m_Window;

	Ref<VertexArray> m_VertexArray;
	Ref<VertexBuffer> m_VertexBuffer;
	Ref<IndexBuffer> m_IndexBuffer;

	Ref<Shader> m_TestShader;
	Ref<Shader> m_TextureShader;

	Ref<Texture> m_Texture;

	Ref<Framebuffer> m_Framebuffer;

	SceneCamera m_SceneCamera;

	ImFont* m_RegularFont;
	ImFont* m_SemiboldFont;

	float bg_col[3] = { 0.09f, 0.09f, 0.1f };
	float grid_col[3] = { 0.17f, 0.17f, 0.17f };
	float camera_pos[3] = { 0.0f, 0.0f, 0.0f };

	float camera_rot = 0.0f;
	float camera_size = 0.0f;
	float camera_fov = 0.0f;

	int gridSize = 5;
	float gridGap = 0.1f;
	float gridLineWidth = 0.006f;

	float imageRotation = 0.0f;

	ImVec2 m_ViewportSize = { 0.0f, 0.0f };
};