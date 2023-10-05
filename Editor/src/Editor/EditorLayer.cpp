#include "Editor/Style/Icons.h"
#include "Editor/EditorLayer.h"
#include "Editor/CobaltEditor.h"

EditorLayer::EditorLayer() : Layer("Editor Layer"), m_Window(Application::GetWindow())
{
	m_EditorFonts = StyleManager::GetEditorFonts();
	m_EditorCamera = CreateRef<EditorCamera>();
	m_ActiveCamera = m_EditorCamera;

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
	m_ViewportPanel = CreateScope<ViewportPanel>(m_Framebuffer, m_EditorCamera, m_ActiveScene);

	m_ParticleSystem = CreateRef<ParticleSystem>();
	m_ParticleSystem->AddGenerator(ParticleGenerator::Create<LifetimeGenerator>());
	m_ParticleSystem->AddGenerator(ParticleGenerator::Create<BoxPositionGenerator>());
	m_ParticleSystem->AddGenerator(ParticleGenerator::Create<VelocityGenerator>());
	m_ParticleEditorPanel = CreateScope<ParticleEditorPanel>(m_ParticleSystem);
}

void EditorLayer::OnUpdate()
{
	PROFILER_START_HEADER("EditorLayer::OnUpdate");

	m_Framebuffer->Bind();

	{
		PROFILER_TIMER_SCOPE("Begin scene");

		RenderCommand::BeginScene(m_ActiveCamera);
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
		PROFILER_TIMER_SCOPE("Particle System");
		m_ParticleSystem->Update();
	}

	{
		PROFILER_TIMER_SCOPE("End scene");
		RenderCommand::EndScene();
	}

	EditorPanelManager::Update();

	{
		PROFILER_TIMER_SCOPE("Editor Camera");
		m_EditorCamera->Update();
	}


	m_Framebuffer->Unbind();

	PROFILER_STOP_HEADER;
}

void EditorLayer::OnImGuiUpdate()
{
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	Vec2 windowPos = m_Window->GetPosition();

	float toolbarHeight = 40.0f;
	float toolbarPadding = 5.0f;

	ImGui::SetNextWindowPos({ viewport->Pos.x, viewport->Pos.y + (toolbarHeight - 10.f)});
	ImGui::SetNextWindowSize({ viewport->Size.x, viewport->Size.y - toolbarHeight + 10.f});
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGuiWindowFlags dockspaceFlags = 0
		| ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking
		| ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse
		| ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::Begin("Master DockSpace", NULL, dockspaceFlags);
	ImGuiID dockMain = ImGui::GetID("MyDockspace");

	ImGui::DockSpace(dockMain);
	ImGui::End();
	ImGui::PopStyleVar(3);

	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize({ viewport->Size.x, toolbarHeight + 10.f });
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGuiWindowFlags toolbarFlags = 0
		| ImGuiWindowFlags_NoDocking
		| ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoScrollbar
		| ImGuiWindowFlags_NoSavedSettings;

	ImGui::PushStyleColor(ImGuiCol_WindowBg, (ImU32)Color(23, 23, 23));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { toolbarPadding, 0 });
	ImGui::Begin("TOOLBAR", NULL, toolbarFlags);

	auto* drawList = ImGui::GetWindowDrawList();
	auto cursor_pos = ImGui::GetCursorScreenPos();
	drawList->AddRectFilled({cursor_pos.x, cursor_pos.y + toolbarPadding}, {cursor_pos.x + 260.f, cursor_pos.y + toolbarPadding + toolbarHeight}, (ImU32)Color(32, 32, 32), 5.f);

	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImU32)Color(45, 45, 45));
	ImGui::PushStyleColor(ImGuiCol_Button, (ImU32)Color(0, 0, 0, 0));
	ImGui::PushStyleColor(ImGuiCol_Text, (ImU32)Color(49, 124, 181));

	float buttonSize = toolbarHeight * 0.7;

	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + toolbarPadding);
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 11.f);
	ImGui::Button(ICON_ARROW_CIRCLE_LEFT, ImVec2(buttonSize, buttonSize));

	ImGui::SameLine();
	ImGui::Button(ICON_ARROW_CIRCLE_RIGHT, ImVec2(buttonSize, buttonSize));
	ImGui::SameLine();
	
	ImGui::PopStyleColor();

	cursor_pos = ImGui::GetCursorScreenPos();
	cursor_pos.x += toolbarPadding;

	drawList->AddLine(cursor_pos, { cursor_pos.x, cursor_pos.y + buttonSize }, (ImU32)Color(42, 42, 42));

	ImGui::PushStyleColor(ImGuiCol_Text, (ImU32)Color(217, 170, 59));
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + toolbarPadding * 4);
	ImGui::Button(ICON_SAVE, ImVec2(buttonSize, buttonSize));
	ImGui::PopStyleColor();

	ImGui::SameLine();

	cursor_pos = ImGui::GetCursorScreenPos();
	cursor_pos.x += toolbarPadding;

	drawList->AddLine(cursor_pos, { cursor_pos.x, cursor_pos.y + buttonSize }, (ImU32)Color(42, 42, 42));

	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + toolbarPadding * 4);
	ImGui::Button("+ Entity", ImVec2(ImGui::CalcTextSize(ICON_PLUS " Entity").x + 10, buttonSize));

	ImGui::PopStyleColor(2);

	ImGui::End();
	ImGui::PopStyleVar(3);
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

		if (ImGui::Checkbox("Vsync", &m_Vsync))
		{
			m_Window->SetVsync(m_Vsync);
		}

		switch (m_ParticleSystem->GetState())
		{
			case ParticleSystemState::None:
			{
				if (ImGui::Button("Start")) { m_ParticleSystem->Start(); }
				break;
			}
			case ParticleSystemState::Updating:
			{
				if (ImGui::Button("Pause")) { m_ParticleSystem->Pause(); }
				break;
			}
			case ParticleSystemState::Stopped:
			{
				if (ImGui::Button("Resume")) { m_ParticleSystem->Resume(); }
				break;
			}
		}

		if (m_ParticleSystem->GetState() != ParticleSystemState::None)
		{
			if (ImGui::Button("Reset")) m_ParticleSystem->Reset();
		}

		ImGui::InputInt("Max particles", (int*)&m_ParticleSystem->GetSpecs().MaxParticles);
		ImGui::SliderInt("Emit rate", (int*)m_ParticleSystem->GetEmitRatePtr(), 1, 10);

		if (ImGui::Button("LOG"))
		{
			LOG_TRACE("Trace message");
			LOG_INFO("Info message");
			LOG_WARN("Warn message");
			LOG_ERROR("Error message");
		}
	}
	ImGui::End();

	EditorPanelManager::ImGuiUpdate();
}

void EditorLayer::OnEvent(Event& event)
{
	m_EditorCamera->OnEvent(event);

	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<LogTraceEvent>(BIND_EVENT_FN(EditorLayer::OnEngineTraceLog));
	dispatcher.Dispatch<LogInfoEvent>(BIND_EVENT_FN(EditorLayer::OnEngineInfoLog));
	dispatcher.Dispatch<LogWarnEvent>(BIND_EVENT_FN(EditorLayer::OnEngineWarnLog));
	dispatcher.Dispatch<LogErrorEvent>(BIND_EVENT_FN(EditorLayer::OnEngineErrorLog));
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
