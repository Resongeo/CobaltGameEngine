#include "cbpch.h"

#include "Cobalt/Platform/OpenGL/OpenGLContext.h"

#include <iostream>
#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Cobalt
{
	OpenGLContext::OpenGLContext(GLFWwindow* glfwWindow) : m_Window(glfwWindow) { }

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_Window);
		if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) < 1)
		{
			COBALT_ERROR("Failed to load GLAD! {}");
			return;
		}
		COBALT_INFO("GLAD loaded OpenGL headers!");
		std::cout << "OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
		std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
		std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}
}