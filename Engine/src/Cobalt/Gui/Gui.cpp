#include "cbpch.h"

#include "Cobalt/Gui/Gui.h"
#include "Cobalt/Core/Application.h"

namespace Cobalt
{
	Scope<ImGuiImpl> Gui::s_ImGuiImpl = nullptr;

	void Gui::Init()
	{
		s_ImGuiImpl = ImGuiImpl::Create(Application::GetWindow()->GetHandle());
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