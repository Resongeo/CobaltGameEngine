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
	fbSpecs.Attachments = { FramebufferAttachmentType::RGBA8, FramebufferAttachmentType::RGBA8, FramebufferAttachmentType::RGBA8, FramebufferAttachmentType::RED_INTEGER };
	fbSpecs.Width = m_Window->GetWidth();
	fbSpecs.Height = m_Window->GetHeight();
	m_Framebuffer = Framebuffer::Create(fbSpecs);

	m_ActiveScene = CreateRef<Scene>("Test Scene"); // TODO: Move this to a SceneManager

	m_LogPanel = CreateScope<LogPanel>();
	m_AssetBrowserPanel = CreateScope<AssetBrowserPanel>(m_ActiveScene, m_SceneHierarchyPanel); // TODO: remove scene from constructor
	m_ProfilerPanel = CreateScope<ProfilerPanel>();
	m_RenderStatisticsPanel = CreateScope<RenderStatisticsPanel>();
	m_ComponentsPanel = CreateScope<ComponentsPanel>();
	m_SceneHierarchyPanel = CreateRef<SceneHierarchyPanel>(m_ActiveScene); // TODO: remove scene from constructor
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
		RenderCommand::BeginScene(*m_ActiveCamera);

		for (float x = -(float)m_GridData.Size; x < m_GridData.Size; x += m_GridData.GapSize)
			RenderCommand::DrawQuad({ x, 0, 0 }, { m_GridData.LineWidth, m_GridData.Size * 2, 0 }, m_GridColor);

		for (float y = -(float)m_GridData.Size; y < m_GridData.Size; y += m_GridData.GapSize)
			RenderCommand::DrawQuad({ 0, y, 0 }, { m_GridData.Size * 2, m_GridData.LineWidth, 0 }, m_GridColor);

		RenderCommand::EndScene();
	}
	
	{
		PROFILER_TIMER_SCOPE("Scene update");
		
		m_ActiveScene->Update(Time::deltaTime);
		m_Framebuffer->ClearAttachment(3, -1);
	}

	{
		PROFILER_TIMER_SCOPE("EndScene");
		RenderCommand::EndScene();

		auto [mx, my] = ImGui::GetMousePos();
		mx -= m_ViewportBounds[0].x;
		my -= m_ViewportBounds[0].y;
		Vec2 viewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];

		my = viewportSize.y - my;

		int mouseX = (int)mx;
		int mouseY = (int)my;

		if (Input::GetMouseButtonDown(0) && !ImGuizmo::IsOver())
		{
			if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y)
			{
				int pixelData = m_Framebuffer->ReadPixel(3, mouseX, mouseY);
				if (pixelData >= 0)
				{
					Entity entity = {(entt::entity)pixelData, m_ActiveScene.get()};
					m_SceneHierarchyPanel->SetSelectedEntity(entity);
				}
				else
				{
					m_SceneHierarchyPanel->DeselectEntity();
				}
			}
		}
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
		auto viewportOffset = ImGui::GetCursorPos();

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		if (m_ViewportSize.x != viewportPanelSize.x || m_ViewportSize.y != viewportPanelSize.y)
		{
			m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
			m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_EditorCamera.SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);
			RenderCommand::SetViewport(0, 0, (uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}

		ImGui::Image((ImTextureID)m_Framebuffer->GetColorAttachmentID(m_FBAttachmentID), m_ViewportSize, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		
		auto windowSize = ImGui::GetWindowSize();
		ImVec2 minBound = ImGui::GetWindowPos();
		minBound.x += viewportOffset.x;
		minBound.y += viewportOffset.y;

		ImVec2 maxBound = { minBound.x + windowSize.x, minBound.y + windowSize.y };
		m_ViewportBounds[0] = { minBound.x, minBound.y };
		m_ViewportBounds[1] = { maxBound.x, maxBound.y };

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
				if (Controls::DrawVector1("Size", m_EditorCamera.GetSizeAdr(), 5.0f, 0.01, 10.0f))
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

		Entity selectedEntity = m_SceneHierarchyPanel->GetSelectedEntity();
		if (selectedEntity)
		{
			ImGuizmo::SetOrthographic(true);
			ImGuizmo::SetDrawlist();

			float windowWidth = ImGui::GetWindowWidth();
			float windowHeight = ImGui::GetWindowHeight();

			ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

			auto& tc = selectedEntity.GetComponent<TransformComponent>();
			Mat4 view = m_EditorCamera.GetViewMatrix();
			Mat4 projection = m_EditorCamera.GetProjectionMatrix();
			Mat4 transform = tc.GetTransform();

			ImGuizmo::Manipulate(glm::value_ptr(view), glm::value_ptr(projection), m_GizmoOperation, m_GizmoMode, glm::value_ptr(transform));

			if (ImGuizmo::IsUsing())
			{
				Vec3 scale;
				Quat rotation;
				Vec3 translation;
				Vec3 skew;
				Vec4 perspective;
				glm::decompose(transform, scale, rotation, translation, skew, perspective);

				switch (m_GizmoOperation)
				{
					case ImGuizmo::OPERATION::TRANSLATE:
						tc.Position = translation;
						break;
					case ImGuizmo::OPERATION::ROTATE:
						tc.Rotation = glm::degrees(glm::eulerAngles(rotation));
						break;
					case ImGuizmo::OPERATION::SCALE:
						tc.Scale = scale;
						break;
				}
			}
		}

		if (Input::GetKeyDown(KEYCODE_1))
			m_GizmoOperation = ImGuizmo::OPERATION::TRANSLATE;

		if (Input::GetKeyDown(KEYCODE_2))
			m_GizmoOperation = ImGuizmo::OPERATION::ROTATE;

		if (Input::GetKeyDown(KEYCODE_3))
			m_GizmoOperation = ImGuizmo::OPERATION::SCALE;


		if (Input::GetKeyDown(KEYCODE_Q))
			m_GizmoMode = ImGuizmo::MODE::LOCAL;

		if (Input::GetKeyDown(KEYCODE_E))
			m_GizmoMode = ImGuizmo::MODE::WORLD;


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

		ImGui::Dummy(ImVec2(0, 30));
		
		const char* ids[] = { "Color", "UV", "UV cooler" };
		ImGui::Combo("##ids", &m_FBAttachmentID, ids, IM_ARRAYSIZE(ids));
		
		ImGui::Dummy(ImVec2(0, 30));
		
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
			DEBUG_LOG("");
			DEBUG_LOG("Random ID: {0}", Random::ID());
		}

		const char* filepath = "..\\assets\\scenes\\TestScene.cbscene";
		if (ImGui::Button("Save scene"))
		{
			SceneSerializer serializer;
			serializer.Serialize(filepath, m_ActiveScene);
		}

		if (ImGui::Button("Load scene"))
		{
			m_SceneHierarchyPanel->DeselectEntity();

			SceneSerializer serializer;
			serializer.Deserialize(FileSystem::OpenFileDialog("Scene files (*.cbscene)\0*.cbscene\0").c_str(), m_ActiveScene);
		}

		if (ImGui::Button("Log entity UUID"))
		{
			auto& entity = SceneHierarchyPanel::GetSelectedEntity();
			if(entity)
				DEBUG_INFO("UUID: {0}", entity.GetComponent<IDComponent>().UUID);
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