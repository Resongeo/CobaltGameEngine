#include "Editor/Style/Icons.h"
#include "Editor/EditorLayer.h"
#include "Editor/CobaltEditor.h"

EditorLayer::EditorLayer() : Layer("Editor Layer"), m_Window(Application::GetWindow())
{
	m_EditorFonts = StyleManager::GetEditorFonts();
	m_ActiveCamera = &m_EditorCamera;

	m_GridData.Size = 5;
	m_GridData.GapSize = 0.1f;
	m_GridData.LineWidth = 0.005f;
}

void EditorLayer::OnAttach()
{
	m_Texture = Texture2D::Create("assets\\textures\\uv_grid.png");

	FramebufferSpecification framebufferSpecs;
	framebufferSpecs.Width = m_Window->GetWidth();
	framebufferSpecs.Height = m_Window->GetHeight();
	m_Framebuffer = Framebuffer::Create(framebufferSpecs);

	m_ActiveScene = CreateRef<Scene>(); // TODO: Move this to a SceneManager

	m_LogPanel = CreateScope<LogPanel>();
	m_AssetBrowserPanel = CreateScope<AssetBrowserPanel>();
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

		RenderCommand::BeginScene(*m_ActiveCamera);
		RenderCommand::Clear();

		RenderCommand::ResetStats();
	}

	m_Framebuffer->Bind();

	{
		PROFILER_TIMER_SCOPE("Clear");

		RenderCommand::ClearColor(m_ClearColor);
		RenderCommand::Clear();
	}

	if(m_ShowGrid)
	{
		PROFILER_TIMER_SCOPE("Grid");

		for (float x = -(float)m_GridData.Size; x < m_GridData.Size; x += m_GridData.GapSize)
			RenderCommand::DrawQuad({ x, 0, 0 }, { m_GridData.LineWidth, m_GridData.Size * 2, 0 }, m_GridColor);

		for (float y = -(float)m_GridData.Size; y < m_GridData.Size; y += m_GridData.GapSize)
			RenderCommand::DrawQuad({ 0, y, 0 }, { m_GridData.Size * 2, m_GridData.LineWidth, 0 }, m_GridColor);
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

	{
		PROFILER_TIMER_SCOPE("EditorCamera");
		m_EditorCamera.Update();
	}

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
			m_EditorCamera.SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);
			RenderCommand::SetViewport(0, 0, (uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}
		ImGui::Image((void*)(uint64_t)m_Framebuffer->GetColorAttachmentID(), m_ViewportSize, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		
		m_EditorCamera.SetMouseOverViewport(ImGui::IsWindowHovered());

		if (m_ShowFps)
		{
			ImGui::SetCursorPosX(30);
			ImGui::SetCursorPosY(20);

			ImGui::PushFont(m_EditorFonts->SemiBold);

			if (Time::intervalFrameRate < 30.f)
				ImGui::TextColored(ImVec4(0.89f, 0.21f, 0.21f, 1.0f), ("FPS: " + std::to_string((int)Time::intervalFrameRate)).c_str());
			else if (Time::intervalFrameRate < 60.f)
				ImGui::TextColored(ImVec4(0.89f, 0.84f, 0.21f, 1.0f), ("FPS: " + std::to_string((int)Time::intervalFrameRate)).c_str());
			else
				ImGui::TextColored(ImVec4(0.41f, 0.89f, 0.21f, 1.0f), ("FPS: " + std::to_string((int)Time::intervalFrameRate)).c_str());

			ImGui::PopFont();
		}

		float width = ImGui::GetWindowWidth();
		ImGui::SetCursorPosX(width - 50.0f);
		ImGui::SetCursorPosY(10.0f);

		if (ImGui::Button(ICON_VIDEO))
		{
			ImGui::SetNextWindowPos({ ImGui::GetMousePos().x + 20, ImGui::GetMousePos().y + 20 }, 0, { 1, 0 });

			ImGui::OpenPopup("EditorCameraSettings");
		}

		ImGui::SetCursorPosX(width - 90.0f);
		ImGui::SetCursorPosY(10.0f);

		if (ImGui::Button(ICON_TABLE))
			m_ShowGrid = !m_ShowGrid;

		if (ImGui::BeginPopup("EditorCameraSettings", ImGuiWindowFlags_NoMove))
		{
			ImGui::Spacing();

			auto windowWidth = ImGui::GetWindowSize().x;
			auto textWidth = ImGui::CalcTextSize(ICON_VIDEO " Settings").x;
			ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);

			ImGui::PushFont(m_EditorFonts->SemiBold);
			ImGui::TextColored(ImVec4(0.176, 0.450, 0.705, 1.0), ICON_VIDEO " Settings");
			ImGui::PopFont();

			const char* proj_types[] = { "Orthographic", "Perspective" };
			static int selected = 0;

			ImGui::Text("Type");
			ImGui::SameLine();
			ImGui::SetNextItemWidth(200.0f);
			ImGui::SetCursorPosX(50.0f);
			if (ImGui::Combo("##type", &selected, proj_types, IM_ARRAYSIZE(proj_types)))
				m_EditorCamera.SetProjectionType(selected == 0 ? ProjectionType::Orthographic : ProjectionType::Perspective);

			if (selected == 0)
			{
				if (Controls::DrawVector1("Size", m_EditorCamera.GetSizeAdr(), 2.0f, 0.01, 10.0f))
					m_EditorCamera.UpdateView();
			}
			else
			{
				if (Controls::DrawVector1("Size", m_EditorCamera.GetFovAdr(), 90.0f, 10.0f, 170.0f))
					m_EditorCamera.UpdateView();
			}

			ImGui::Columns(1);

			ImGui::EndPopup();
		}

		ImGui::End();
		ImGui::PopStyleVar();
	}

	{
		PROFILER_TIMER_SCOPE("Test window");

		ImGui::Begin("Test window");

		ImGui::ColorEdit4("BG color", glm::value_ptr(m_ClearColor));

		ImGui::PushFont(m_EditorFonts->SemiBold);
		ImGui::Spacing();
		if (ImGui::Button("Reset BG color", ImVec2(ImGui::GetWindowSize().x * 0.95f, 40.0f)))
			m_ClearColor = { 0.09f, 0.09f, 0.1f, 1.0f };
		ImGui::PopFont();

		ImGui::Dummy(ImVec2(0, 30));

		if (ImGui::Checkbox("Vsync", &m_Vsync)) m_Window->SetVsync(m_Vsync);
		ImGui::Checkbox("Show FPS", &m_ShowFps);

		if (ImGui::Button(ICON_FOLDER_OPEN " Open File Dialog"))
			FileSystem::OpenFileDialog("Text files (*.txt)\0*.txt\0");
		if (ImGui::Button(ICON_SAVE " Save File Dialog"))
			FileSystem::SaveFileDialog("Text files (*.txt)\0*.txt\0");

		ImGui::Dummy({ 0, 10 });

		ImGui::DragFloat("Mouse pan speed", m_EditorCamera.GetPanSpeed(), 0.1f, 0.1f, 10.0f);

		ImGui::Dummy({ 0, 10 });

		if(ImGui::Button("Get random number"))
		{
			DEBUG_CLEAR;
			DEBUG_LOG("Random: {0}", Random::RangeInt(0, 10));
			DEBUG_INFO("Random: {0}", Random::RangeInt(0, 10));
			DEBUG_WARN("Random: {0}", Random::RangeInt(0, 10));
			DEBUG_ERROR("Random: {0}", Random::RangeInt(0, 10));
		}

		ImGui::End();
	}

	PROFILER_STOP_HEADER;

	EditorPanelManager::Update();
}

void EditorLayer::OnEvent(Event& event)
{
	m_EditorCamera.OnEvent(event);
}