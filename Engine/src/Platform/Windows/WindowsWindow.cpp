#include "cbpch.h"

#ifdef _WIN32

#include "Platform/Window.h"
#include "Renderer/Renderer.h"

#include <dwmapi.h>

#ifndef DWMWA_USE_IMMERSIVE_DARK_MODE
#define DWMWA_USE_IMMERSIVE_DARK_MODE 20
#endif

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace Cobalt
{
	Window::Window(const WindowProperties& properties)
	{
		m_Properties = properties;

		m_Data.Title = properties.Title;
		m_Data.Width = properties.Width;
		m_Data.Height = properties.Height;

		if (!glfwInit())
			LOG_ENGINE_ERROR("Failed to initialize GLFW!");

		LOG_ENGINE_INFO("GLFW initialized");

		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::OpenGL:
			{
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, COBALT_OPENGL_VERSION_MAJOR);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, COBALT_OPENGL_VERSION_MINOR);
				glfwWindowHint(GLFW_OPENGL_PROFILE, COBALT_OPENGL_PROFILE);

				break;
			}
		}

		m_Window = glfwCreateWindow(m_Properties.Width, m_Properties.Height, m_Properties.Title.c_str(), nullptr, nullptr);
		if (m_Window == nullptr)
			LOG_ENGINE_ERROR("Failed to create window!");
		
		LOG_ENGINE_INFO("Window created: {0}x{1} title: {2}", m_Properties.Width, m_Properties.Height, m_Properties.Title.c_str());

		m_GraphicsContext = GraphicsContext::Create(m_Window);
		m_GraphicsContext->Init();

		HWND hWnd = glfwGetWin32Window(m_Window);
		BOOL value = TRUE;
		DwmSetWindowAttribute(hWnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &value, sizeof(value));

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVsync(true);

		/* Callbacks */
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});

		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		int sys_width = mode->width;
		int sys_height = mode->height;
		glfwSetWindowMonitor(m_Window, nullptr,
			(sys_width / 2) - (m_Properties.Width / 2),
			(sys_height / 2) - (m_Properties.Height / 2),
			m_Properties.Width, m_Properties.Height, GLFW_DONT_CARE);
	}

	Ref<Window> Window::Create(const WindowProperties& properties)
	{
		return CreateRef<Window>(properties);
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
	}

	void Window::SetHeight(uint32_t height)
	{
		m_Properties.Height = height;
		glfwSetWindowSize(m_Window, m_Properties.Width, m_Properties.Height);
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

	bool Window::ShouldClose()
	{
		return glfwWindowShouldClose(m_Window);
	}

	void Window::Update()
	{
		glfwPollEvents();
		m_GraphicsContext->SwapBuffers();
	}
}

#endif