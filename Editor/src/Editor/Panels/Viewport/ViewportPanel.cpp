#include "Editor/Panels/Viewport/ViewportPanel.h"
#include "Editor/Utils/Controls.h"

#include "Editor/CobaltEditor.h"

ViewportPanel* ViewportPanel::s_Instance = nullptr;
ViewportPanel::ViewportPanel(const Ref<Framebuffer>& framebuffer, EditorCamera* editorCamera, const Ref<Scene>& activeScene)
	: m_Framebuffer(framebuffer), m_EditorCamera(editorCamera), m_ActiveScene(activeScene), EditorPanel("Viewport")
{
	s_Instance = this;
}

void ViewportPanel::Update()
{
	if (CobaltEditor::GetEditorLayer()->SceneState == SceneState::Play) return;

	auto [mx, my] = ImGui::GetMousePos();
	mx -= m_ViewportBounds[0].x;
	my -= m_ViewportBounds[0].y;
	Vec2 viewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];

	my = viewportSize.y - my;

	int mouseX = (int)mx;
	int mouseY = (int)my;

	if (Input::GetMouseButtonClicked(MOUSE_BUTTON_LEFT) && !ImGuizmo::IsOver())
	{
		if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y)
		{
			int pixelData = m_Framebuffer->ReadPixel(3, mouseX, mouseY);

			if (pixelData >= 0)
			{
				Entity entity = { (entt::entity)pixelData, m_ActiveScene.get() };
				SceneHierarchyPanel::SetSelectedEntity(entity);
			}
			else
			{
				SceneHierarchyPanel::DeselectEntity();
			}
		}
	}

	m_SelectedEntity = SceneHierarchyPanel::GetSelectedEntity();

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
}

void ViewportPanel::ImGuiUpdate()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
	ImGui::Begin("Viewport");
	auto viewportOffset = ImGui::GetCursorPos();

	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	if (m_ViewportSize.x != viewportPanelSize.x || m_ViewportSize.y != viewportPanelSize.y)
	{
		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
		m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		m_EditorCamera->SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);
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

	m_EditorCamera->SetMouseOverViewport(ImGui::IsWindowHovered());

	if (m_ShowFPS)
	{
		ImGui::SetCursorPosX(30);
		ImGui::SetCursorPosY(20);

		ImGui::PushFont(p_EditorFonts->SemiBold);

		if (Time::intervalFrameRate < 30.f)
			ImGui::TextColored(ImVec4(0.89f, 0.21f, 0.21f, 1.0f), "FPS: %d", (int)Time::intervalFrameRate);
		else if (Time::intervalFrameRate < 60.f)
			ImGui::TextColored(ImVec4(0.89f, 0.84f, 0.21f, 1.0f), "FPS: %d", (int)Time::intervalFrameRate);
		else
			ImGui::TextColored(ImVec4(0.41f, 0.89f, 0.21f, 1.0f), "FPS: %d", (int)Time::intervalFrameRate);

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

		ImGui::PushFont(p_EditorFonts->SemiBold);
		ImGui::TextColored(ImVec4(0.176f, 0.450f, 0.705f, 1.0f), ICON_VIDEO " Settings");
		ImGui::PopFont();

		const char* proj_types[] = { "Orthographic", "Perspective" };
		static int selected = 0;

		ImGui::Text("Type");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(200.0f);
		ImGui::SetCursorPosX(50.0f);
		if (ImGui::Combo("##type", &selected, proj_types, IM_ARRAYSIZE(proj_types)))
			m_EditorCamera->SetProjectionType(selected == 0 ? ProjectionType::Orthographic : ProjectionType::Perspective);

		if (selected == 0)
		{
			if (Controls::DrawVector1("Size", m_EditorCamera->GetSizeAdr(), { 0, 0 }, 5.0f, 0.01f, 10.0f))
				m_EditorCamera->UpdateView();
		}
		else
		{
			if (Controls::DrawVector1("Size", m_EditorCamera->GetFovAdr(), { 0, 0 }, 90.0f, 10.0f, 170.0f))
				m_EditorCamera->UpdateView();
		}

		ImGui::Columns(1);
		ImGui::EndPopup();
	}

	if (m_SelectedEntity && CobaltEditor::GetEditorLayer()->SceneState == SceneState::Edit)
	{
		ImGuizmo::SetOrthographic(true);
		ImGuizmo::SetDrawlist();

		float windowWidth = ImGui::GetWindowWidth();
		float windowHeight = ImGui::GetWindowHeight();

		ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

		auto& tc = m_SelectedEntity.GetComponent<TransformComponent>();
		Mat4 view = m_EditorCamera->GetViewMatrix();
		Mat4 projection = m_EditorCamera->GetProjectionMatrix();
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

	ImGui::End();
	ImGui::PopStyleVar();
}
