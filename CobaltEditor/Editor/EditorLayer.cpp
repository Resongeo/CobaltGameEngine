#include "Editor/EditorLayer.h"
#include "Editor/CobaltEditor.h"

EditorLayer::EditorLayer() : Layer("Editor Layer"), m_Window(Application::Get().GetWindow())
{
	m_SceneCameraData.Position = m_SceneCamera.GetPosition();
	m_SceneCameraData.Rotation = m_SceneCamera.GetRotation();
	m_SceneCameraData.Size = m_SceneCamera.GetSize();
	m_SceneCameraData.FOV = m_SceneCamera.GetFOV();

	m_GridData.Size = 5;
	m_GridData.GapSize = 0.1f;
	m_GridData.LineWidth = 0.005f;
}

void EditorLayer::OnAttach()
{
	LOG_WARN("Layer: {0} attached!", m_DebugName);
	ImGuiStyle* style = &ImGui::GetStyle();

	style->WindowTitleAlign = ImVec2(0.5, 0.5);
	style->WindowRounding = 8.0f;
	style->FrameRounding = 4.0f;
	style->GrabRounding = 3.0f;
	style->WindowPadding = ImVec2(10, 10);
		
	style->Colors[ImGuiCol_WindowBg] = ImColor(26, 26, 26, 255);
	style->Colors[ImGuiCol_Border] = ImColor(20, 20, 20, 255);

	style->Colors[ImGuiCol_Text] = ImColor(240, 240, 240);
	style->Colors[ImGuiCol_CheckMark] = ImColor(164, 208, 217);
	style->Colors[ImGuiCol_ResizeGrip] = ImColor(115, 160, 220, 51);
	style->Colors[ImGuiCol_DockingPreview] = ImColor(157, 192, 197);
	style->Colors[ImGuiCol_DragDropTarget] = ImColor(166, 180, 195);
	style->Colors[ImGuiCol_ScrollbarBg] = ImColor(0, 0, 0, 50);

	style->Colors[ImGuiCol_SliderGrab] = ImColor(126, 179, 217);
	style->Colors[ImGuiCol_SliderGrabActive] = ImColor(126, 179, 217, 150);

	style->Colors[ImGuiCol_TitleBg] = ImColor(20, 20, 21);
	style->Colors[ImGuiCol_TitleBgActive] = ImColor(20, 20, 21);

	style->Colors[ImGuiCol_FrameBg] = ImColor(255, 255, 255, 30);
	style->Colors[ImGuiCol_FrameBgHovered] = ImColor(255, 255, 255, 80);
	style->Colors[ImGuiCol_FrameBgActive] = ImColor(48, 48, 48, 150);

	style->Colors[ImGuiCol_Tab] = ImColor(68, 80, 86);
	style->Colors[ImGuiCol_TabHovered] = ImColor(81, 119, 134);
	style->Colors[ImGuiCol_TabActive] = ImColor(48, 49, 51);
	style->Colors[ImGuiCol_TabUnfocused] = ImColor(0, 0, 0, 0);
	style->Colors[ImGuiCol_TabUnfocusedActive] = ImColor(0, 0, 0, 0);

	style->Colors[ImGuiCol_Button] = ImColor(17, 17, 17);
	style->Colors[ImGuiCol_ButtonHovered] = ImColor(100, 150, 200, 180);
	style->Colors[ImGuiCol_ButtonActive] = ImColor(95, 134, 170, 80);

	style->Colors[ImGuiCol_Header] = ImColor(26, 26, 26, 255);
	style->Colors[ImGuiCol_HeaderHovered] = ImColor(26, 26, 26, 255);
	style->Colors[ImGuiCol_HeaderActive] = ImColor(26, 26, 26, 255);

	style->Colors[ImGuiCol_Separator] = ImColor(50, 55, 58, 255);
	style->Colors[ImGuiCol_SeparatorActive] = ImColor(116, 151, 170, 200);
	style->Colors[ImGuiCol_SeparatorHovered] = ImColor(84, 109, 123, 255);

	ImGuiIO& io = ImGui::GetIO();
	m_EditorFonts.Regular = io.Fonts->AddFontFromFileTTF("assets\\fonts\\Poppins-Regular.ttf", 20.0f);
	m_EditorFonts.SemiBold = io.Fonts->AddFontFromFileTTF("assets\\fonts\\Poppins-Semibold.ttf", 20.0f);

	m_Texture = Texture::Create("assets\\textures\\uv_grid.png");

	FramebufferSpecification framebufferSpecs;
	framebufferSpecs.Width = m_Window.GetWidth();
	framebufferSpecs.Height = m_Window.GetHeight();
	m_Framebuffer = Framebuffer::Create(framebufferSpecs);

	m_ActiveScene = CreateRef<Scene>();
	//m_ActiveScene->CreateEntity();

	m_LogPanel = CreateScope<LogPanel>();
	m_SceneHierarchyPanel = CreateScope<SceneHierarchyPanel>(m_ActiveScene);
}

void EditorLayer::OnUpdate(float deltaTime)
{
	RenderCommand::BeginScene(m_SceneCamera);
	RenderCommand::Clear();

	m_Framebuffer->Bind();

	RenderCommand::ClearColor(m_ClearColor);
	RenderCommand::Clear();

	for (float x = -m_GridData.Size; x < m_GridData.Size; x += m_GridData.GapSize)
	{
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(x, 0.0f, 0.0f));
		transform = glm::scale(transform, glm::vec3(m_GridData.LineWidth, m_GridData.Size * 2.0f, 1.0f));

		RenderCommand::DrawQuad(transform, m_GridColor);
	}

	for (float y = -m_GridData.Size; y < m_GridData.Size; y += m_GridData.GapSize)
	{
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(0.0f, y, 0.0f));
		transform = glm::scale(transform, glm::vec3(m_GridData.Size * 2.0f, m_GridData.LineWidth, 1.0f));

		RenderCommand::DrawQuad(transform, m_GridColor);
	}
		
	m_ActiveScene->Update(deltaTime);

	m_Framebuffer->Unbind();

	if (Input::GetKeyDown(KEYCODE_A))
		m_SceneCameraData.Position.x -= 1.0f * deltaTime;
	else if (Input::GetKeyDown(KEYCODE_D))
		m_SceneCameraData.Position.x += 1.0f * deltaTime;

	if (Input::GetKeyDown(KEYCODE_W))
		m_SceneCameraData.Position.y += 1.0f * deltaTime;
	else if (Input::GetKeyDown(KEYCODE_S))
		m_SceneCameraData.Position.y -= 1.0f * deltaTime;

	m_SceneCamera.SetPosition(m_SceneCameraData.Position);

	m_LogPanel->Update(deltaTime);
	m_SceneHierarchyPanel->Update(deltaTime);
}

// TODO: Move all time related stuff into its own class
float fpsRefreshInterval = 0.5f;
float nextTimeToRefreshFPS = 1.0f;
float fpsCounter = 0.0f;

bool isVsync = true;
bool showFps = true;

int entity_count = 1;

void EditorLayer::OnImGuiUpdate(float deltaTime)
{
	if (fpsRefreshInterval < 0.0f)
	{
		fpsCounter = 1.0f / deltaTime;
		fpsRefreshInterval = nextTimeToRefreshFPS;
	}
	else
	{
		fpsRefreshInterval -= deltaTime;
	}

	/* Viewport */
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });

		ImGui::Begin("Viewport");

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		if (m_ViewportSize.x != viewportPanelSize.x || m_ViewportSize.y != viewportPanelSize.y)
		{
			m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
			m_Framebuffer->Resize(m_ViewportSize.x, m_ViewportSize.y);
			m_SceneCamera.SetAspectRatio(m_ViewportSize.x, m_ViewportSize.y);
			RenderCommand::SetViewport(0, 0, m_ViewportSize.x, m_ViewportSize.y);
		}
		ImGui::Image((void*)m_Framebuffer->GetColorAttachmentID(), m_ViewportSize, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		if (showFps)
		{
			ImGui::SetCursorPosX(30);
			ImGui::SetCursorPosY(30);

			if (fpsCounter < 30.f)
				ImGui::TextColored(ImVec4(0.89f, 0.21f, 0.21f, 1.f), ("FPS: " + std::to_string((int)fpsCounter)).c_str());
			else if (fpsCounter < 60.f)
				ImGui::TextColored(ImVec4(0.89f, 0.84f, 0.21f, 1.f), ("FPS: " + std::to_string((int)fpsCounter)).c_str());
			else
				ImGui::TextColored(ImVec4(0.41f, 0.89f, 0.21f, 1.f), ("FPS: " + std::to_string((int)fpsCounter)).c_str());
		}

		ImGui::End();
		ImGui::PopStyleVar();
	}

	/* Test window */
	{
		ImGui::Begin("Test window");

		ImGui::PushFont(m_EditorFonts.SemiBold);
		if (ImGui::Button("Press me!"))
		{
			LOG_TRACE("You pressed me :)");
			DEBUG_LOG("You pressed me :)");
		}
		ImGui::PopFont();

		ImGui::Dummy(ImVec2(0, 30));

		ImGui::ColorEdit4("BG color", glm::value_ptr(m_ClearColor));

		ImGui::PushFont(m_EditorFonts.SemiBold);
		ImGui::Spacing();
		if (ImGui::Button("Reset BG color", ImVec2(ImGui::GetWindowSize().x * 0.95f, 40.0f)))
			m_ClearColor = { 0.09f, 0.09f, 0.1f, 1.0f };
		ImGui::PopFont();

		ImGui::Dummy(ImVec2(0, 30));

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.258f, 0.76f, 0.391f, 1.0f));
		if (ImGui::Button("Add UV grid", ImVec2(ImGui::GetWindowSize().x * 0.95f, 0.0f)))
		{
			for (int i = 0; i < 100; i++)
			{
				auto entity = m_ActiveScene->CreateEntity();
				entity.AddComponent<SpriteRendererComponent>(m_Texture, glm::vec4(1.0));

				DEBUG_WARN(fmt::format("{0} entites", entity_count));
				entity_count++;
			}
		}
		ImGui::PopStyleColor();

		ImGui::Dummy(ImVec2(0, 30));

		if (ImGui::Checkbox("Vsync", &isVsync)) m_Window.SetVsync(isVsync);
		ImGui::Checkbox("Show FPS", &showFps);

		ImGui::End();
	}

	/* Settings */
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 10));
	{
		ImGuiStyle* style = &ImGui::GetStyle();

		ImGui::Begin("Settings");

		style->FrameRounding = 0.0f;
		if (m_CameraSettingsOpened)
		{
			style->Colors[ImGuiCol_Header] = ImColor(0, 0, 0, 100);
			style->Colors[ImGuiCol_HeaderActive] = ImColor(0, 0, 0, 100);
			style->Colors[ImGuiCol_HeaderHovered] = ImColor(0, 0, 0, 100);
		}

		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 8));
		if (ImGui::CollapsingHeader("Camera"))
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 3));
			style->FrameRounding = 4.0f;

			const char* projectionTypes[] = { "Orthographic", "Perspective" };
			static int current_projection = 0;
			ImGui::SetCursorPosX(10);
			if (ImGui::Combo("Projection", &current_projection, projectionTypes, IM_ARRAYSIZE(projectionTypes)))
			{
				m_SceneCamera.SetProjectionType(current_projection == 0 ? ProjectionType::Orthographic : ProjectionType::Perspective);
			}

			ImGui::Text("");

			ImGui::SetCursorPosX(10);
			ImGui::DragFloat3("Camera position", glm::value_ptr(m_SceneCameraData.Position), 0.1f);
			if (ImGui::DragFloat("Rotation", &m_SceneCameraData.Rotation, 0.1)) m_SceneCamera.SetRotaion(m_SceneCameraData.Rotation);

			ImGui::Text("");

			if (current_projection == 0)
			{
				ImGui::SetCursorPosX(10);
				if (ImGui::DragFloat("Size", &m_SceneCameraData.Size, 0.1)) m_SceneCamera.SetSize(m_SceneCameraData.Size);
			}
			else
			{
				ImGui::SetCursorPosX(10);
				if (ImGui::DragFloat("FOV", &m_SceneCameraData.FOV, 0.1)) m_SceneCamera.SetFOV(m_SceneCameraData.FOV);
			}

			m_CameraSettingsOpened = true;

			ImGui::PopStyleVar();
		}
		else
		{
			m_CameraSettingsOpened = false;
		}
		ImGui::PopStyleVar();

		style->Colors[ImGuiCol_Header] = ImColor(26, 26, 26, 255);
		style->Colors[ImGuiCol_HeaderActive] = ImColor(26, 26, 26, 255);
		style->Colors[ImGuiCol_HeaderHovered] = ImColor(26, 26, 26, 255);


		ImGui::Spacing();

		style->FrameRounding = 0.0f;
		if (m_GridSettingsOpened)
		{
			style->Colors[ImGuiCol_Header] = ImColor(0, 0, 0, 100);
			style->Colors[ImGuiCol_HeaderActive] = ImColor(0, 0, 0, 100);
			style->Colors[ImGuiCol_HeaderHovered] = ImColor(0, 0, 0, 100);
		}

		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 8));
		if (ImGui::CollapsingHeader("Grid"))
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 3));
			style->FrameRounding = 4.0f;

			ImGui::Spacing();
			ImGui::SetCursorPosX(10);
			ImGui::ColorEdit3("Grid color", glm::value_ptr(m_GridColor));
			ImGui::Spacing();

			ImGui::SetCursorPosX(10);
			ImGui::SliderInt("Grid size", &m_GridData.Size, 1, 10);
				
			ImGui::SetCursorPosX(10);
			ImGui::SliderFloat("Grid gap", &m_GridData.GapSize, 0.02f, 1.0f);
				
			ImGui::SetCursorPosX(10);
			ImGui::SliderFloat("Grid line width", &m_GridData.LineWidth, 0.001f, 0.1f);

			ImGui::Spacing();

			ImGui::PushFont(m_EditorFonts.SemiBold);
			ImGui::SetCursorPosX(10);
			if (ImGui::Button("Reset grid", ImVec2(ImGui::GetWindowSize().x * 0.95f, 40.0f)))
			{
				m_GridData.Size = 5;
				m_GridData.GapSize = 0.1f;
				m_GridData.LineWidth = 0.005f;

				m_GridColor = { 0.17f, 0.17f, 0.17f, 1.0f };
			}
			ImGui::PopFont();
				
			m_GridSettingsOpened = true;

			ImGui::PopStyleVar();
		}
		else
		{
			m_GridSettingsOpened = false;
		}
		ImGui::PopStyleVar();

		style->Colors[ImGuiCol_Header] = ImColor(26, 26, 26, 255);
		style->Colors[ImGuiCol_HeaderActive] = ImColor(26, 26, 26, 255);
		style->Colors[ImGuiCol_HeaderHovered] = ImColor(26, 26, 26, 255);

		ImGui::End();

		style->FrameRounding = 4.0f;
	}
	ImGui::PopStyleVar();
}
