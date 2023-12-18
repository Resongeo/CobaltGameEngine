#include "pch.h"
#include "CobaltEditor/Panels/MainViewportPanel.h"
#include "CobaltEditor/Panels/SceneHierarchyPanel.h"

#include "CobaltEditor/Managers/EditorPanelManager.h"

namespace CobaltEditor
{
	MainViewportPanel::MainViewportPanel()
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

	void MainViewportPanel::OnUpdate()
	{
		m_Scene = SceneManager::GetActiveScene();

		m_Viewport->Begin();
		{
			RenderCommand::BeginScene(m_EditorCamera);

			RenderCommand::ClearColor(Color(18, 18, 19));
			RenderCommand::Clear();

			DrawGrid();

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

	void MainViewportPanel::OnUIRender()
	{
		ScopedStyleVar _(ImGuiStyleVar_WindowPadding, { 0, 0 });

		ImGui::Begin("Main Viewport", nullptr, ImGuiWindowFlags_NoDecoration);
		{
			m_ViewportOffset = ImGui::GetCursorPos();

			ResizeViewport();
			m_Viewport->Draw(0);
			UpdateBounds();

			if (m_SelectedEntity)
			{
				DrawGizmo();
			}
		
			m_EditorCamera->SetMouseOverViewport(ImGui::IsWindowHovered());
		}
		ImGui::End();
	}

	void MainViewportPanel::OnEvent(Event& event)
	{
		m_EditorCamera->OnEvent(event);
	}

	Ref<MainViewportPanel> MainViewportPanel::Create()
	{
		auto panel = CreateRef<MainViewportPanel>();
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
		auto windowSize = ImGui::GetWindowSize();
		ImVec2 minBound = ImGui::GetWindowPos();
		minBound.x += m_ViewportOffset.x;
		minBound.y += m_ViewportOffset.y;

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

	inline void MainViewportPanel::DrawGrid()
	{
		int halfSize = 9;
		Color thickColor = Color(25, 25, 26);
		Color thinColor = Color(22, 22, 23);

		for (int y = -halfSize; y < halfSize + 1; y++)
		{
			RenderCommand::DrawQuad(Vec3(0.0f, y, 0.0f), Vec3(halfSize * 2, 0.025f, 1), thickColor);
		}
		for (int x = -halfSize; x < halfSize + 1; x++)
		{
			RenderCommand::DrawQuad(Vec3(x, 0.0f, 0.0f), Vec3(0.025f, halfSize * 2, 1), thickColor);
		}

		for (float y = -halfSize; y < halfSize; y += 0.25f)
		{
			RenderCommand::DrawQuad(Vec3(0.0f, y, 0.0f), Vec3(halfSize * 2, 0.01f, 1), thinColor);
		}
		for (float x = -halfSize; x < halfSize; x += 0.25f)
		{
			RenderCommand::DrawQuad(Vec3(x, 0.0f, 0.0f), Vec3(0.01f, halfSize * 2, 1), thinColor);
		}
	}
}