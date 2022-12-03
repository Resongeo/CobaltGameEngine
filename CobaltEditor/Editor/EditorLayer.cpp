#include "Editor/EditorLayer.h"
#include "Editor/CobaltEditor.h"

#include "Editor/Debug/LogLayer.h"

namespace Cobalt
{
	EditorLayer::EditorLayer() : Layer("Editor Layer"), m_Window(Application::Get().GetWindow())
	{
		camera_pos[0] = m_SceneCamera.GetPosition().x;
		camera_pos[1] = m_SceneCamera.GetPosition().y;
		camera_pos[2] = m_SceneCamera.GetPosition().z;

		camera_rot = m_SceneCamera.GetRotation();
		camera_size = m_SceneCamera.GetSize();
		camera_fov = m_SceneCamera.GetFOV();

		m_GridEntity;
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
		style->Colors[ImGuiCol_WindowBg] = ImColor(32, 33, 35);

		style->Colors[ImGuiCol_Text] = ImColor(240, 240, 240);
		style->Colors[ImGuiCol_CheckMark] = ImColor(164, 208, 217);
		style->Colors[ImGuiCol_ResizeGrip] = ImColor(115, 160, 220, 51);
		style->Colors[ImGuiCol_DockingPreview] = ImColor(157, 192, 197);
		style->Colors[ImGuiCol_DragDropTarget] = ImColor(166, 180, 195);
		style->Colors[ImGuiCol_ScrollbarBg] = ImColor(0, 0, 0, 50);

		style->Colors[ImGuiCol_SliderGrab] = ImColor(126, 179, 217);
		style->Colors[ImGuiCol_SliderGrabActive] = ImColor(126, 179, 217, 150);

		style->Colors[ImGuiCol_TitleBg] = ImColor(26, 26, 26);
		style->Colors[ImGuiCol_TitleBgActive] = ImColor(60, 60, 60);

		style->Colors[ImGuiCol_FrameBg] = ImColor(255, 255, 255, 44);
		style->Colors[ImGuiCol_FrameBgHovered] = ImColor(255, 255, 255, 100);
		style->Colors[ImGuiCol_FrameBgActive] = ImColor(48, 48, 48, 150);

		style->Colors[ImGuiCol_Tab] = ImColor(68, 80, 86);
		style->Colors[ImGuiCol_TabHovered] = ImColor(81, 119, 134);
		style->Colors[ImGuiCol_TabActive] = ImColor(48, 49, 51);
		style->Colors[ImGuiCol_TabUnfocused] = ImColor(0, 0, 0, 0);
		style->Colors[ImGuiCol_TabUnfocusedActive] = ImColor(0, 0, 0, 0);

		style->Colors[ImGuiCol_Button] = ImColor(95, 134, 170);
		style->Colors[ImGuiCol_ButtonHovered] = ImColor(95, 134, 170, 150);
		style->Colors[ImGuiCol_ButtonActive] = ImColor(95, 134, 170, 80);

		style->Colors[ImGuiCol_Header] = ImColor(69, 79, 96);
		style->Colors[ImGuiCol_HeaderHovered] = ImColor(105, 116, 137);
		style->Colors[ImGuiCol_HeaderActive] = ImColor(69, 79, 96, 150);

		style->Colors[ImGuiCol_Separator] = ImColor(50, 55, 58, 255);
		style->Colors[ImGuiCol_SeparatorActive] = ImColor(116, 151, 170, 200);
		style->Colors[ImGuiCol_SeparatorHovered] = ImColor(84, 109, 123, 255);

		ImGuiIO& io = ImGui::GetIO();
		m_RegularFont = io.Fonts->AddFontFromFileTTF("assets\\fonts\\Poppins-Regular.ttf", 20.0f);
		m_SemiboldFont = io.Fonts->AddFontFromFileTTF("assets\\fonts\\Poppins-Semibold.ttf", 20.0f);

		m_Texture = Texture::Create("assets\\textures\\uv_grid.png");

		FramebufferSpecification framebufferSpecs;
		framebufferSpecs.Width = m_Window.GetWidth();
		framebufferSpecs.Height = m_Window.GetHeight();
		m_Framebuffer = Framebuffer::Create(framebufferSpecs);

		m_ActiveScene = CreateRef<Scene>();
	}

	void EditorLayer::OnUpdate(float deltaTime)
	{
		RenderCommand::BeginScene(m_SceneCamera);
		RenderCommand::Clear();

		m_Framebuffer->Bind();

		RenderCommand::ClearColor({ bg_col[0], bg_col[1], bg_col[2], 1.0 });
		RenderCommand::Clear();

		for (float x = -gridSize; x < gridSize; x += gridGap)
		{
			glm::mat4 transform = glm::mat4(1.0f);
			transform = glm::translate(transform, glm::vec3(x, 0.0f, 0.0f));
			transform = glm::scale(transform, glm::vec3(gridLineWidth, gridSize * 2.0f, 1.0f));

			RenderCommand::DrawQuad(transform, {0.2, 0.2, 0.2, 1.0});
		}

		for (float y = -gridSize; y < gridSize; y += gridGap)
		{
			glm::mat4 transform = glm::mat4(1.0f);
			transform = glm::translate(transform, glm::vec3(0.0f, y, 0.0f));
			transform = glm::scale(transform, glm::vec3(gridSize * 2.0f, gridLineWidth, 1.0f));

			RenderCommand::DrawQuad(transform, { 0.2, 0.2, 0.2, 1.0 });
		}
		
		m_ActiveScene->Update(deltaTime);

		glm::mat4 imageTransform = glm::mat4(1.0);
		imageTransform = glm::rotate(imageTransform, glm::radians(imageRotation), glm::vec3(0.0, 0.0, 1.0));
		imageRotation += deltaTime * 5.0f;


		/*RenderCommand::DrawIndexed(m_TextureShader, m_VertexArray, imageTransform); */

		m_Framebuffer->Unbind();

		if (Input::GetKeyDown(KEYCODE_A))
			camera_pos[0] -= 1.0f * deltaTime;
		else if (Input::GetKeyDown(KEYCODE_D))
			camera_pos[0] += 1.0f * deltaTime;

		if (Input::GetKeyDown(KEYCODE_W))
			camera_pos[1] += 1.0f * deltaTime;
		else if (Input::GetKeyDown(KEYCODE_S))
			camera_pos[1] -= 1.0f * deltaTime;
	}

	void EditorLayer::OnImGuiUpdate(float deltaTime)
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

		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::Begin("Debug window");

		ImGui::PushFont(m_SemiboldFont);
		if (ImGui::Button("Press me!"))
		{
			LOG_TRACE("You pressed me :)");
			DEBUG_LOG("You pressed me :)");
		}
		ImGui::PopFont();
		ImGui::Text("");
		ImGui::ColorEdit3("BG color", bg_col);
		ImGui::PushFont(m_SemiboldFont);
		if (ImGui::Button("Reset BG color"))
		{
			bg_col[0] = 0.09f;
			bg_col[1] = 0.09f;
			bg_col[2] = 0.10f;
		}
		ImGui::PopFont();

		ImGui::Text("");

		if (ImGui::CollapsingHeader("Grid", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::Spacing();
			ImGui::ColorEdit3("Grid color", grid_col);
			ImGui::Spacing();

			ImGui::SliderInt("Grid size", &gridSize, 1, 10);
			ImGui::SliderFloat("Grid gap", &gridGap, 0.02f, 1.0f);
			ImGui::SliderFloat("Grid line width", &gridLineWidth, 0.001f, 0.1f);

			ImGui::Spacing();

			ImGui::PushFont(m_SemiboldFont);
			if (ImGui::Button("Reset grid"))
			{
				gridSize = 5;
				gridGap = 0.1f;
				gridLineWidth = 0.006f;

				grid_col[0] = 0.17f;
				grid_col[1] = 0.17f;
				grid_col[2] = 0.17f;
			}
			ImGui::PopFont();

			ImGui::Text("");
			ImGui::Text("");

			if (ImGui::Button("Add sprite"))
			{
				m_GridEntity = m_ActiveScene->CreateEntity();
				m_GridEntity.AddComponent<SpriteRendererComponent>(m_Texture, glm::vec4(1.0));
			}

			if (m_GridEntity)
			{
				ImGui::Text(m_GridEntity.GetComponent<TagComponent>().Tag.c_str());
			}
		}

		ImGui::End();
		ImGui::Begin("Camera");
		const char* projectionTypes[] = { "Orthographic", "Perspective" };
		static int current_projection = 0;
		if (ImGui::Combo("Projection", &current_projection, projectionTypes, IM_ARRAYSIZE(projectionTypes)))
		{
			m_SceneCamera.SetProjectionType(current_projection == 0 ? ProjectionType::Orthographic : ProjectionType::Perspective);
		}

		ImGui::Text("");

		ImGui::DragFloat3("Camera position", camera_pos, 0.1f);
		m_SceneCamera.SetPosition({ camera_pos[0], camera_pos[1], camera_pos[2] });
		if (ImGui::DragFloat("Rotation", &camera_rot, 0.1)) m_SceneCamera.SetRotaion(camera_rot);

		ImGui::Text("");

		if (current_projection == 0)
		{
			if (ImGui::DragFloat("Size", &camera_size, 0.1)) m_SceneCamera.SetSize(camera_size);
		}
		else
		{
			if (ImGui::DragFloat("FOV", &camera_fov, 0.1)) m_SceneCamera.SetFOV(camera_fov);
		}

		ImGui::End();
	}
}
