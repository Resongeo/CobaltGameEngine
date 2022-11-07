#include "Cobalt.h"

class ExampleLayer : public Cobalt::Layer
{
public:
	ExampleLayer() : Layer("Example Layer")
	{
		float vertices[4 * 3] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		unsigned int indices[6] =
		{
			0, 1, 3,
			1, 2, 3
		};

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
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
	}

	void OnUpdate() override
	{
		glClearColor(0.05, 0.4, 0.6, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(m_VertexArray);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		ImGui::Begin("Debug window");

		if (ImGui::Button("Press me!")) LOG_TRACE("You pressed me :)");

		ImGui::End();
	}

private:
	unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
};

class Sandbox : public Cobalt::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

int main()
{
	Sandbox* sandbox = new Sandbox();
	sandbox->Run();
	delete sandbox;

	return 0;
}
