#include "Cobalt.h"
using namespace Cobalt;

#include "fonts/FontAwesomeIcons.h"

class ExampleLayer : public Layer
{
public:
	ExampleLayer() : Layer("Example Layer")
	{
		float vertices[4 * 8] =
		{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.3f, 0.3f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 0.3f, 0.8f, 0.3f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 0.3f, 0.3f, 0.8f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.8f, 0.3f, 0.3f, 0.0f, 1.0f
		};

		unsigned int indices[6] =
		{
			0, 1, 3,
			1, 2, 3
		};

		m_VertexArray = VertexArray::Create();
		m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		m_IndexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int));

		BufferLayout layout =
		{
			{ ShaderDataType::Float3, "aPosition" },
			{ ShaderDataType::Float3, "aColor" },
			{ ShaderDataType::Float2, "aTexCoord" }
		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		std::string vertexSource = R"(
			#version 460 core
			
			layout(location = 0) in vec3 aPosition;
			layout(location = 1) in vec3 aColor;

			uniform mat4 View;
			uniform mat4 Model;

			out vec3 TexCoords;
			out vec3 vColor;

			void main()
			{
				gl_Position = View * Model * vec4(aPosition, 1.0);
				TexCoords = aPosition.xyz;
				vColor = aColor;
			}
		)";
		std::string fragmentSource = R"(
			#version 460 core
			
			layout(location = 0) out vec4 FragColor;
			in vec3 TexCoords;
			in vec3 vColor;

			uniform vec3 inColor;

			void main()	 
			{
				FragColor = vec4(inColor, 1.0);
			}
		)";

		m_Shader = Shader::Create(vertexSource, fragmentSource, ShaderSourceType::String);
		camera_pos[0] = m_SceneCamera.GetPosition().x;
		camera_pos[1] = m_SceneCamera.GetPosition().y;
		camera_pos[2] = m_SceneCamera.GetPosition().z;

		camera_rot = m_SceneCamera.GetRotation();
		camera_size = m_SceneCamera.GetSize();
		camera_fov = m_SceneCamera.GetFOV();

		auto window = Application::Get().GetWindow();
		window.SetVsync(false);
	}
	
	void OnAttach() override
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
		io.Fonts->AddFontDefault();

		ImFontConfig config;
		config.MergeMode = true;
		config.PixelSnapH = true;
		config.GlyphMaxAdvanceX = 20.0f;
		static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };

		regularFont = io.Fonts->AddFontFromFileTTF("fonts\\Poppins-Regular.ttf", 20.0f);
		semiboldFont = io.Fonts->AddFontFromFileTTF("fonts\\Poppins-Semibold.ttf", 20.0f);
		iconFont = io.Fonts->AddFontFromFileTTF("fonts\\fa-regular-400.ttf", 20.0f, &config, icon_ranges);
	}

	void OnUpdate(float deltaTime) override
	{
		RenderCommand::BeginScene(m_SceneCamera);

		RenderCommand::ClearColor({ bg_col[0], bg_col[1], bg_col[2], 1.0 });
		RenderCommand::Clear();

		m_Shader->Bind();
		m_Shader->SetVec3("inColor", grid_col[0], grid_col[1], grid_col[2]);


		for (float x = -gridSize; x < gridSize; x += gridGap)
		{
			glm::mat4 transform = glm::mat4(1.0f);
			transform = glm::translate(transform, glm::vec3(x, 0.0f, 0.0f));
			transform = glm::scale(transform, glm::vec3(gridLineWidth, gridSize * 2.0f, 1.0f));

			RenderCommand::DrawIndexed(m_Shader, m_VertexArray, transform);
		}

		for (float y = -gridSize; y < gridSize; y += gridGap)
		{
			glm::mat4 transform = glm::mat4(1.0f);
			transform = glm::translate(transform, glm::vec3(0.0f, y, 0.0f));
			transform = glm::scale(transform, glm::vec3(gridSize * 2.0f, gridLineWidth, 1.0f));

			RenderCommand::DrawIndexed(m_Shader, m_VertexArray, transform);
		}

		{
			ImGui::Begin("Debug window");
			
			ImGui::PushFont(iconFont);
			ImGui::Text(ICON_FA_APPLE_WHOLE);
			ImGui::PopFont();

			ImGui::PushFont(semiboldFont);
			if (ImGui::Button("Press me!")) LOG_TRACE("You pressed me :)");
			ImGui::PopFont();
			ImGui::Text("");
			ImGui::ColorEdit3("BG color", bg_col);
			ImGui::PushFont(semiboldFont);
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

				ImGui::PushFont(semiboldFont);
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

			if(current_projection == 0)
			{
				if (ImGui::DragFloat("Size", &camera_size, 0.1)) m_SceneCamera.SetSize(camera_size);
			}
			else
			{
				if (ImGui::DragFloat("FOV", &camera_fov, 0.1)) m_SceneCamera.SetFOV(camera_fov);
			}

			ImGui::End();
		}

		ImGui::ShowDemoWindow();

		if (Input::GetKeyDown(KEYCODE_A))
			camera_pos[0] -= 1.0f * deltaTime;
		else if(Input::GetKeyDown(KEYCODE_D))
			camera_pos[0] += 1.0f * deltaTime;

		if (Input::GetKeyDown(KEYCODE_W))
			camera_pos[1] += 1.0f * deltaTime;
		else if (Input::GetKeyDown(KEYCODE_S))
			camera_pos[1] -= 1.0f * deltaTime;
		
	}

private:
	Ref<VertexArray> m_VertexArray;
	Ref<VertexBuffer> m_VertexBuffer;
	Ref<IndexBuffer> m_IndexBuffer;
	Ref<Shader> m_Shader;

	SceneCamera m_SceneCamera;

	float bg_col[3] = { 0.09f, 0.09f, 0.1f };
	float grid_col[3] = { 0.17f, 0.17f, 0.17f };
	float camera_pos[3] = { 0.0f, 0.0f, 0.0f };

	float camera_rot = 0.0f;
	float camera_size = 0.0f;
	float camera_fov = 0.0f;

	int gridSize = 5;
	float gridGap = 0.1f;
	float gridLineWidth = 0.006f;

	ImFont* regularFont;
	ImFont* semiboldFont;
	ImFont* iconFont;
};

class Sandbox : public Application
{
public:
	Sandbox(const ApplicationSpecification& applicationSpecifiacion) : Application(applicationSpecifiacion)
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

int main()
{
	ApplicationSpecification appSpecs;
	appSpecs.WindowProperties.Width = 1920;
	appSpecs.WindowProperties.Height = 1080;

	Sandbox* sandbox = new Sandbox(appSpecs);
	sandbox->Run();
	delete sandbox;

	return 0;
}
