#include "Editor/Style/Icons.h"
#include "Editor/EditorLayer.h"
#include "Editor/CobaltEditor.h"

EditorLayer::EditorLayer() : Layer("Editor Layer"), m_Window(Application::GetWindow())
{
	m_EditorFonts = StyleManager::GetEditorFonts();
	m_ActiveCamera = &m_EditorCamera;

	m_GridData.Size = 5;
	m_GridData.GapSize = 0.5f;
	m_GridData.LineWidth = 0.015f;
}

void EditorLayer::OnAttach()
{
	FramebufferSpecification fbSpecs;
	fbSpecs.Attachments = { FramebufferAttachmentType::RGBA8, FramebufferAttachmentType::RED_INTEGER };
	fbSpecs.Width = m_Window->GetWidth();
	fbSpecs.Height = m_Window->GetHeight();
	fbSpecs.Samples = 1;
	m_Framebuffer = Framebuffer::Create(fbSpecs);

	m_ActiveScene = CreateRef<Scene>("Test Scene"); // TODO: Move this to a SceneManager

	m_LogPanel = CreateScope<LogPanel>();
	m_AssetBrowserPanel = CreateScope<AssetBrowserPanel>(m_ActiveScene); // TODO: remove scene from constructor
	m_ProfilerPanel = CreateScope<ProfilerPanel>();
	m_RenderStatisticsPanel = CreateScope<RenderStatisticsPanel>();
	m_ComponentsPanel = CreateScope<ComponentsPanel>();
	m_SceneHierarchyPanel = CreateRef<SceneHierarchyPanel>(m_ActiveScene); // TODO: remove scene from constructor
	m_ViewportPanel = CreateScope<ViewportPanel>(m_Framebuffer, &m_EditorCamera, m_ActiveScene);
}

void EditorLayer::OnUpdate()
{
	PROFILER_START_HEADER("EditorLayer::OnUpdate");

	m_Framebuffer->Bind();

	{
		PROFILER_TIMER_SCOPE("Begin scene");

		RenderCommand::BeginScene(*m_ActiveCamera);
		RenderCommand::ClearColor(m_ClearColor);
		RenderCommand::Clear();
		RenderCommand::ResetStats();
	}

	if(ViewportPanel::IsGridShown())
	{
		PROFILER_TIMER_SCOPE("Grid");

		for (float x = -(float)m_GridData.Size; x < m_GridData.Size; x += m_GridData.GapSize)
			RenderCommand::DrawQuad({ x, 0, 0 }, { m_GridData.LineWidth, m_GridData.Size * 2, 0 }, m_GridColor);

		for (float y = -(float)m_GridData.Size; y < m_GridData.Size; y += m_GridData.GapSize)
			RenderCommand::DrawQuad({ 0, y, 0 }, { m_GridData.Size * 2, m_GridData.LineWidth, 0 }, m_GridColor);

		RenderCommand::EndScene();
	}
	
	{
		PROFILER_TIMER_SCOPE("Scene update");
		
		switch (SceneState)
		{
			case SceneState::Edit:
				m_ActiveScene->EditorUpdate();
				break;
			case SceneState::Play:
				m_ActiveScene->RuntimeUpdate();
				break;
			case SceneState::Simulate:
				break;
		}

		m_Framebuffer->ClearAttachment(1, -1);
	}

	{
		PROFILER_TIMER_SCOPE("End scene");
		RenderCommand::EndScene();
	}

	EditorPanelManager::Update();

	{
		PROFILER_TIMER_SCOPE("Editor Camera");
		m_EditorCamera.Update();
	}

	m_Framebuffer->Unbind();

	PROFILER_STOP_HEADER;
}

void EditorLayer::OnImGuiUpdate()
{
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	Vec2 windowPos = m_Window->GetPosition();

	ImGui::SetNextWindowPos({ viewport->WorkPos.x + m_SideBarWidth, viewport->WorkPos.y + m_TopBarHeight });
	ImGui::SetNextWindowSize({ viewport->WorkSize.x - m_SideBarWidth, viewport->WorkSize.y - m_TopBarHeight - m_BottomBarHeight });
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGuiWindowFlags host_window_flags = 0;
	host_window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDocking;
	host_window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	if (0 & ImGuiDockNodeFlags_PassthruCentralNode)
		host_window_flags |= ImGuiWindowFlags_NoBackground;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("MainDockSpaceViewport", NULL, host_window_flags);
	ImGui::PopStyleVar(3);

	ImGuiID dockspace_id = ImGui::GetID("DockSpace");
	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f));
	ImGui::End();

	ImGuiWindowFlags barFlags = ImGuiWindowFlags_NoSavedSettings;
	barFlags |= ImGuiWindowFlags_NoMove;
	barFlags |= ImGuiWindowFlags_NoDecoration;


	ImGui::PushStyleColor(ImGuiCol_WindowBg, { 255, 0, 0, 0 });

	
	ImGui::SetNextWindowPos({ viewport->WorkPos.x, viewport->WorkPos.y});
	ImGui::SetNextWindowSize({ viewport->WorkSize.x, m_TopBarHeight });

	ImGui::Begin("##TopBar", nullptr, barFlags);
	ImGui::SetWindowFocus();
	ImGui::End();


	ImGui::SetNextWindowPos({ viewport->WorkPos.x, viewport->WorkPos.y });
	ImGui::SetNextWindowSize({ m_SideBarWidth, viewport->WorkSize.y });

	ImGui::Begin("##SideBar", nullptr, barFlags);
	ImGui::End();


	ImGui::PopStyleColor();

	ImGui::Begin("Test");
	{
		if (ImGui::Button("Run scene"))
		{
			if (SceneState == SceneState::Edit)
			{
				m_ActiveScene->RuntimeStart();
				SceneState = SceneState::Play;
			}
			else if (SceneState == SceneState::Play)
			{
				SceneState = SceneState::Edit;
			}
		}

		switch (SceneState)
		{
		case Cobalt::SceneState::Edit:
			ImGui::Text("Editing...");
			break;
		case Cobalt::SceneState::Play:
			ImGui::Text("Playing...");
			break;
		}

		if (ImGui::Button("LOG"))
		{
			DEBUG_LOG("Debug: Log message");
			DEBUG_INFO("Debug: Info message");
			DEBUG_WARN("Debug: Warn message");
			DEBUG_ERROR("Debug: Error message");
		}

		if (ImGui::Checkbox("Vsync", &m_Vsync))
		{
			m_Window->SetVsync(m_Vsync);
		}

		ImGui::SliderFloat("Top bar", &m_TopBarHeight, 0.0f, 100.0f);
		ImGui::SliderFloat("Side bar", &m_SideBarWidth, 0.0f, 100.0f);
		ImGui::SliderFloat("Bottom bar", &m_BottomBarHeight, 0.0f, 100.0f);
	}
	ImGui::End();

	EditorPanelManager::ImGuiUpdate();
}

void EditorLayer::OnEvent(Event& event)
{
	m_EditorCamera.OnEvent(event);

	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<LogTraceEvent>(CB_BIND_EVENT_FN(EditorLayer::OnEngineTraceLog));
	dispatcher.Dispatch<LogInfoEvent>(CB_BIND_EVENT_FN(EditorLayer::OnEngineInfoLog));
	dispatcher.Dispatch<LogWarnEvent>(CB_BIND_EVENT_FN(EditorLayer::OnEngineWarnLog));
	dispatcher.Dispatch<LogErrorEvent>(CB_BIND_EVENT_FN(EditorLayer::OnEngineErrorLog));
}

bool EditorLayer::OnEngineTraceLog(LogTraceEvent& event)
{
	DEBUG_LOG("{}", event.GetLogMessage());
	return false;
}

bool EditorLayer::OnEngineInfoLog(LogInfoEvent& event)
{
	DEBUG_INFO("{}", event.GetLogMessage());
	return false;
}

bool EditorLayer::OnEngineWarnLog(LogWarnEvent& event)
{
	DEBUG_WARN("{}", event.GetLogMessage());
	return false;
}

bool EditorLayer::OnEngineErrorLog(LogErrorEvent& event)
{
	DEBUG_ERROR("{}", event.GetLogMessage());
	return false;
}
