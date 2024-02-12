#include "cbpch.h"

#include "Cobalt/Gui/ImGuiImpl.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <ImGuizmo.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Cobalt
{
	ImGuiImpl::ImGuiImpl()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true);
		ImGui_ImplOpenGL3_Init(OPENGL_VERSION_STRING);
	}

	void ImGuiImpl::NewFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGuizmo::BeginFrame();
	}
	
	void ImGuiImpl::Render()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backupCurrentContext);
		}
	}
	
	void ImGuiImpl::ShutDown()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	Unique<ImGuiImpl> ImGuiImpl::Create()
	{
		return CreateUnique<ImGuiImpl>();
	}
}