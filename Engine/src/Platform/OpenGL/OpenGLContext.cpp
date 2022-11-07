#include "Platform/OpenGL/OpenGLContext.h"

namespace Cobalt
{
	OpenGLContext::OpenGLContext(GLFWwindow* glfwWindow) : m_Window(glfwWindow) { }

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_Window);
		if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) < 1)
		{
			LOG_ENGINE_ERROR("Failed to load GLAD!");
			return;
		}
		LOG_ENGINE_INFO("GLAD loaded OpenGL headers!");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}
}