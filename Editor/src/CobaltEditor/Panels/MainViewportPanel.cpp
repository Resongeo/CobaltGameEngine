#include "CobaltEditor/Panels/MainViewportPanel.h"

#include "CobaltEditor/Managers/EditorPanelManager.h"

namespace CobaltEditor
{
	MainViewportPanel::MainViewportPanel(const Ref<Cobalt::Scene>& scene) : m_Scene(scene)
	{
		Cobalt::FramebufferSpecification framebufferSpecs;
		framebufferSpecs.Attachments =
		{
			Cobalt::FramebufferAttachmentType::RGBA8,
			Cobalt::FramebufferAttachmentType::RED_INTEGER
		};
		framebufferSpecs.Samples = 1;
		
		m_Viewport = Viewport::Create({ 100, 100 }, framebufferSpecs);
		m_EditorCamera = CreateRef<Cobalt::EditorCamera>();
	}

	void MainViewportPanel::Update()
	{
		m_Viewport->Begin();
		{
			Cobalt::RenderCommand::BeginScene(m_EditorCamera);

			Cobalt::RenderCommand::ClearColor(Cobalt::Color(21, 21, 23));
			Cobalt::RenderCommand::Clear();

			m_Scene->EditorUpdate();
			m_Viewport->GetFramebuffer()->ClearAttachment(1, -1);

			Cobalt::RenderCommand::EndScene();

			auto [mx, my] = ImGui::GetMousePos();
			mx -= m_ViewportBounds[0].x;
			my -= m_ViewportBounds[0].y;
			Vec2 viewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];

			my = viewportSize.y - my;

			int mouseX = (int)mx;
			int mouseY = (int)my;

			if (Cobalt::Input::GetMouseButtonClicked(MOUSE_BUTTON_LEFT) && !ImGuizmo::IsOver())
			{
				if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y)
				{
					int pixelData = m_Viewport->ReadPixel(1, mouseX, mouseY);

					if (pixelData >= 0)
					{
						Cobalt::Entity entity = { (entt::entity)pixelData, m_Scene.get() };
						Cobalt::LOG_TRACE("Entity name: {}", entity.GetComponent<Cobalt::TagComponent>().Tag);
					}
				}
			}
		}
		m_Viewport->End();

		m_EditorCamera->Update();
	}

	void MainViewportPanel::UIRender()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Main Viewport", nullptr, ImGuiWindowFlags_NoDecoration);
		{
			auto viewportOffset = ImGui::GetCursorPos();

			ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
			if (m_ViewportSize.x != viewportPanelSize.x || m_ViewportSize.y != viewportPanelSize.y)
			{
				m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
				m_Viewport->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
				m_EditorCamera->SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);
				Cobalt::RenderCommand::SetViewport(0, 0, (uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			}

			m_Viewport->Draw(0);

			auto windowSize = ImGui::GetWindowSize();
			ImVec2 minBound = ImGui::GetWindowPos();
			minBound.x += viewportOffset.x;
			minBound.y += viewportOffset.y;

			ImVec2 maxBound = { minBound.x + windowSize.x, minBound.y + windowSize.y };
			m_ViewportBounds[0] = { minBound.x, minBound.y };
			m_ViewportBounds[1] = { maxBound.x, maxBound.y };

			m_EditorCamera->SetMouseOverViewport(ImGui::IsWindowHovered());
		}
		ImGui::End();
		ImGui::PopStyleVar();
	}

	Ref<MainViewportPanel> MainViewportPanel::Create(const Ref<Cobalt::Scene>& scene)
	{
		auto panel = CreateRef<MainViewportPanel>(scene);
		EditorPanelManager::PushPanel(panel);
		
		return panel;
	}
}