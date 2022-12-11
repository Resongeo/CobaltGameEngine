#include "Gui/Gui.h"

namespace Cobalt
{
	Scope<ImGuiImpl> Gui::s_ImGuiImpl = nullptr;

	void Gui::Init(GLFWwindow* window)
	{
		s_ImGuiImpl = ImGuiImpl::Create(window);
	}

	void Gui::NewFrame()
	{
		s_ImGuiImpl->NewFrame();
	}
	
	void Gui::Render()
	{
		s_ImGuiImpl->Render();
	}
	
	void Gui::ShutDown()
	{
		s_ImGuiImpl->ShutDown();
	}
}