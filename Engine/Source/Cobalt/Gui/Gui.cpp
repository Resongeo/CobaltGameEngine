#include "cbpch.h"

#include "Cobalt/Gui/Gui.h"

namespace Cobalt
{
	Unique<ImGuiImpl> Gui::s_ImGuiImpl = nullptr;

	void Gui::Init()
	{
		s_ImGuiImpl = ImGuiImpl::Create();
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