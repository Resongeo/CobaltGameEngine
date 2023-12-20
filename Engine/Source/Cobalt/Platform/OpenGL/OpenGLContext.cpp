#include "cbpch.h"

#include "Cobalt/Platform/OpenGL/OpenGLContext.h"

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
			LOG_ERROR("Failed to load GLAD!");
			return;
		}
		LOG_INFO("GLAD loaded OpenGL headers!");
		LOG_INFO("OpenGL version: {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
		LOG_INFO("OpenGL vendor: {}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
		LOG_INFO("OpenGL GLSL version: {}", reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)));
		LOG_INFO("OpenGL renderer: {}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}
}