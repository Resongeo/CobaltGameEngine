#include "Window.h"

namespace Cobalt
{
	Window::Window(const WindowProperties& properties)
	{
		m_Properties = properties;
	}

	bool Window::Create()
	{
		if (!glfwInit())
		{
			LOG_ENGINE_ERROR("Failed to initialize GLFW!");
			return false;
		}

		m_Window = glfwCreateWindow(m_Properties.Width, m_Properties.Height, m_Properties.Title.c_str(), nullptr, nullptr);
		if (m_Window == nullptr)
		{
			LOG_ENGINE_ERROR("Failed to create window!");
			return false;
		}

		glfwMakeContextCurrent(m_Window);

		/* Callbacks */

		glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		});

		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		int sys_width = mode->width;
		int sys_height = mode->height;
		glfwSetWindowMonitor(m_Window, nullptr, 
			(sys_width / 2) - (m_Properties.Width / 2),
			(sys_height / 2) - (m_Properties.Height / 2),
			m_Properties.Width, m_Properties.Height, GLFW_DONT_CARE);

		return true;
	}

	WindowProperties Window::GetProperties()
	{
		int width, height;
		glfwGetFramebufferSize(m_Window, &width, &height);
		
		m_Properties.Width = width;
		m_Properties.Height = height;

		return m_Properties;
	}

	void Window::SetWidth(uint32_t width)
	{
		m_Properties.Width = width;
		glfwSetWindowSize(m_Window, m_Properties.Width, m_Properties.Height);
		glViewport(0, 0, m_Properties.Width, m_Properties.Height);
	}

	void Window::SetHeight(uint32_t height)
	{
		m_Properties.Height = height;
		glfwSetWindowSize(m_Window, m_Properties.Width, m_Properties.Height);
		glViewport(0, 0, m_Properties.Width, m_Properties.Height);
	}

	void Window::SetTitle(const std::string& title)
	{
		m_Properties.Title = title;
		glfwSetWindowTitle(m_Window, m_Properties.Title.c_str());
	}

	void Window::SetVsync(bool value)
	{
		m_Properties.Vsync = value;
		glfwSwapInterval((int)value);
	}

	void Window::Destroy()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}
}