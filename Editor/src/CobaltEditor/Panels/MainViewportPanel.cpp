#include "pch.h"
#include "CobaltEditor/Panels/MainViewportPanel.h"
#include "CobaltEditor/Panels/SceneHierarchyPanel.h"

#include "CobaltEditor/Managers/EditorPanelManager.h"

namespace CobaltEditor
{
	MainViewportPanel::MainViewportPanel(const Ref<Scene>& scene) : m_Scene(scene)
	{
		FramebufferSpecification framebufferSpecs;
		framebufferSpecs.Attachments =
		{
			FramebufferAttachmentType::RGBA8,
			FramebufferAttachmentType::RED_INTEGER
		};
		framebufferSpecs.Samples = 1;
		
		m_Viewport = Viewport::Create({ 100, 100 }, framebufferSpecs);
		m_EditorCamera = CreateRef<EditorCamera>();
	}

	void MainViewportPanel::Update()
	{
		m_Viewport->Begin();
		{
			RenderCommand::BeginScene(m_EditorCamera);

			RenderCommand::ClearColor(Color(21, 21, 23));
			RenderCommand::Clear();

			m_Scene->EditorUpdate();
			m_Viewport->GetFramebuffer()->ClearAttachment(1, -1);

			RenderCommand::EndScene();

			MousePick();
		}
		m_Viewport->End();

		m_EditorCamera->Update();

		m_SelectedEntity = SceneHierarchyPanel::GetSelectedEntity();

		if (Input::GetKeyDown(KEYCODE_1)) m_GizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
		if (Input::GetKeyDown(KEYCODE_2)) m_GizmoOperation = ImGuizmo::OPERATION::ROTATE;
		if (Input::GetKeyDown(KEYCODE_3)) m_GizmoOperation = ImGuizmo::OPERATION::SCALE;

		if (Input::GetKeyDown(KEYCODE_Q)) m_GizmoMode = ImGuizmo::MODE::LOCAL;
		if (Input::GetKeyDown(KEYCODE_E)) m_GizmoMode = ImGuizmo::MODE::WORLD;
	}

	void MainViewportPanel::UIRender()
	{
		ScopedStyleVar _(ImGuiStyleVar_WindowPadding, { 0, 0 });

		ImGui::Begin("Main Viewport", nullptr, ImGuiWindowFlags_NoDecoration);
		{
			ResizeViewport();
			m_Viewport->Draw(0);
			UpdateBounds();
		}

		if (m_SelectedEntity)
		{
			DrawGizmo();
		}
		
		m_EditorCamera->SetMouseOverViewport(ImGui::IsWindowHovered());

		ImGui::End();
	}

	Ref<MainViewportPanel> MainViewportPanel::Create(const Ref<Scene>& scene)
	{
		auto panel = CreateRef<MainViewportPanel>(scene);
		EditorPanelManager::PushPanel(panel);
		
		return panel;
	}

	inline void MainViewportPanel::ResizeViewport()
	{
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		if (m_ViewportSize.x != viewportPanelSize.x || m_ViewportSize.y != viewportPanelSize.y)
		{
			m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
			m_Viewport->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_EditorCamera->SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);
			RenderCommand::SetViewport(0, 0, (uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}
	}

	inline void MainViewportPanel::UpdateBounds()
	{
		auto viewportOffset = ImGui::GetCursorPos();

		auto windowSize = ImGui::GetWindowSize();
		ImVec2 minBound = ImGui::GetWindowPos();
		minBound.x += viewportOffset.x;
		minBound.y += viewportOffset.y;

		ImVec2 maxBound = { minBound.x + windowSize.x, minBound.y + windowSize.y };
		m_ViewportBounds[0] = { minBound.x, minBound.y };
		m_ViewportBounds[1] = { maxBound.x, maxBound.y };
	}

	inline void MainViewportPanel::DrawGizmo()
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

	inline void MainViewportPanel::MousePick()
	{
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
				int pixelData = m_Viewport->ReadPixel(1, mouseX, mouseY);

				if (pixelData >= 0)
				{
					Entity entity = { (entt::entity)pixelData, m_Scene.get() };
					SceneHierarchyPanel::SetSelectedEntity(entity);
				}
				else
				{
					SceneHierarchyPanel::DeselectEntity();
				}
			}
		}
	}
}