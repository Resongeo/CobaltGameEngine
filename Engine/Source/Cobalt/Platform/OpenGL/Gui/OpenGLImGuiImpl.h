#pragma once

#include "Cobalt/Gui/ImGuiImpl.h"

namespace Cobalt
{
	class OpenGLImGuiImpl : public ImGuiImpl
	{
	public:
		OpenGLImGuiImpl(GLFWwindow* window);

		virtual void NewFrame() override;
		virtual void Render() override;
		virtual void ShutDown() override;

	private:
		GLFWwindow* m_GLFWWindow;
	};
}