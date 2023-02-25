#include "Editor/EditorLayer.h"
#include "Editor/CobaltEditor.h"

EditorLayer::EditorLayer() : Layer("Editor Layer"), m_Window(Application::GetWindow())
{
	// TODO: Temporary
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

	// TODO: Move this to a style editor
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

	style->Colors[ImGuiCol_Header] = ImColor(37, 37, 37, 255);
	style->Colors[ImGuiCol_HeaderHovered] = ImColor(48, 48, 48, 255);
	style->Colors[ImGuiCol_HeaderActive] = ImColor(26, 26, 26, 255);

	style->Colors[ImGuiCol_Separator] = ImColor(50, 55, 58, 255);
	style->Colors[ImGuiCol_SeparatorActive] = ImColor(116, 151, 170, 200);
	style->Colors[ImGuiCol_SeparatorHovered] = ImColor(84, 109, 123, 255);

	ImGuiIO& io = ImGui::GetIO();
	m_EditorFonts.Regular = io.Fonts->AddFontFromFileTTF("assets\\fonts\\Poppins-Regular.ttf", 20.0f);
	m_EditorFonts.SemiBold = io.Fonts->AddFontFromFileTTF("assets\\fonts\\Poppins-Semibold.ttf", 20.0f);

	m_Texture = Texture::Create("assets\\textures\\uv_grid.png");

	FramebufferSpecification framebufferSpecs;
	framebufferSpecs.Width = m_Window->GetWidth();
	framebufferSpecs.Height = m_Window->GetHeight();
	m_Framebuffer = Framebuffer::Create(framebufferSpecs);

	m_ActiveScene = CreateRef<Scene>();

	EditorPanelSystem::Init();

	m_LogPanel = CreateScope<LogPanel>();
	m_ProfilerPanel = CreateScope<ProfilerPanel>();
	m_RenderStatisticsPanel = CreateScope<RenderStatisticsPanel>();
	m_ComponentsPanel = CreateScope<ComponentsPanel>();
	m_SceneHierarchyPanel = CreateScope<SceneHierarchyPanel>(m_ActiveScene); // TODO: remove scene from constructor
}

void EditorLayer::OnUpdate()
{
	PROFILER_START_HEADER("EditorLayer::OnUpdate");

	{
		PROFILER_TIMER_SCOPE("BeginScene");

		RenderCommand::BeginScene(m_SceneCamera);
		RenderCommand::Clear();

		RenderCommand::ResetStats();
	}

	m_Framebuffer->Bind();

	{
		PROFILER_TIMER_SCOPE("Clear");

		RenderCommand::ClearColor(m_ClearColor);
		RenderCommand::Clear();
	}

	{
		PROFILER_TIMER_SCOPE("Grid");

		for (float x = -(float)m_GridData.Size; x < m_GridData.Size; x += m_GridData.GapSize)
			RenderCommand::DrawQuad({ x, 0, 0 }, { m_GridData.LineWidth, m_GridData.Size * 2, 0 }, m_GridColor);

		for (float y = -(float)m_GridData.Size; y < m_GridData.Size; y += m_GridData.GapSize)
			RenderCommand::DrawQuad({ 0, y, 0 }, { m_GridData.Size * 2, m_GridData.LineWidth, 0 }, m_GridColor);

		for (float y = -2.0f; y < 2.0f; y += 0.1f)
		{
			for (float x = -2.0f; x < 2.0f; x += 0.1f)
			{
				//RenderCommand::DrawQuad({ x, y, 0.0f }, glm::vec3(0.085f), {(x + 2.0f) / 4.0f, 0.5f, (y + 2.0f) / 4.0f, 1.0f});
			}
		}
	}
	
	{
		PROFILER_TIMER_SCOPE("Scene update");

		m_ActiveScene->Update(Time::deltaTime);
	}

	{
		PROFILER_TIMER_SCOPE("EndScene");
		RenderCommand::EndScene();
	}

	m_Framebuffer->Unbind();

	// TODO: New camera
	if (Input::GetKeyDown(KEYCODE_A))
		m_SceneCameraData.Position.x -= 1.0f * Time::deltaTime;
	else if (Input::GetKeyDown(KEYCODE_D))
		m_SceneCameraData.Position.x += 1.0f * Time::deltaTime;

	if (Input::GetKeyDown(KEYCODE_W))
		m_SceneCameraData.Position.y += 1.0f * Time::deltaTime;
	else if (Input::GetKeyDown(KEYCODE_S))
		m_SceneCameraData.Position.y -= 1.0f * Time::deltaTime;

	m_SceneCamera.SetPosition(m_SceneCameraData.Position);

	PROFILER_STOP_HEADER;
}

// TODO: Move these to their own classes
void EditorLayer::OnImGuiUpdate()
{
	PROFILER_START_HEADER("EditorLayer::OnImGuiUpdate");

	{
		PROFILER_TIMER_SCOPE("Viewport");

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });

		ImGui::Begin("Viewport");

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		if (m_ViewportSize.x != viewportPanelSize.x || m_ViewportSize.y != viewportPanelSize.y)
		{
			m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
			m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_SceneCamera.SetAspectRatio(m_ViewportSize.x, m_ViewportSize.y);
			RenderCommand::SetViewport(0, 0, (uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}
		ImGui::Image((void*)(uint64_t)m_Framebuffer->GetColorAttachmentID(), m_ViewportSize, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		if (m_ShowFps)
		{
			ImGui::SetCursorPosX(30);
			ImGui::SetCursorPosY(30);

			ImGui::PushFont(m_EditorFonts.SemiBold);

			if (Time::intervalFrameRate < 30.f)
				ImGui::TextColored(ImVec4(0.89f, 0.21f, 0.21f, 1.f), ("FPS: " + std::to_string((int)Time::intervalFrameRate)).c_str());
			else if (Time::intervalFrameRate < 60.f)
				ImGui::TextColored(ImVec4(0.89f, 0.84f, 0.21f, 1.f), ("FPS: " + std::to_string((int)Time::intervalFrameRate)).c_str());
			else
				ImGui::TextColored(ImVec4(0.41f, 0.89f, 0.21f, 1.f), ("FPS: " + std::to_string((int)Time::intervalFrameRate)).c_str());

			ImGui::PopFont();
		}

		ImGui::End();
		ImGui::PopStyleVar();
	}

	{
		PROFILER_TIMER_SCOPE("Test window");

		ImGui::Begin("Test window");

		ImGui::ColorEdit4("BG color", glm::value_ptr(m_ClearColor));

		ImGui::PushFont(m_EditorFonts.SemiBold);
		ImGui::Spacing();
		if (ImGui::Button("Reset BG color", ImVec2(ImGui::GetWindowSize().x * 0.95f, 40.0f)))
			m_ClearColor = { 0.09f, 0.09f, 0.1f, 1.0f };
		ImGui::PopFont();

		ImGui::Dummy(ImVec2(0, 30));

		if (ImGui::Checkbox("Vsync", &m_Vsync)) m_Window->SetVsync(m_Vsync);
		ImGui::Checkbox("Show FPS", &m_ShowFps);

		if (ImGui::Button("Open File Dialog"))
			FileSystem::OpenFileDialog("Text files (*.txt)\0*.txt\0");
		if (ImGui::Button("Save File Dialog"))
			FileSystem::SaveFileDialog("Text files (*.txt)\0*.txt\0");

		ImGui::End();
	}

	PROFILER_STOP_HEADER;

	EditorPanelSystem::Update();
}
