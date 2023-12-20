#include "cbpch.h"

#ifdef _WIN32

#include "Cobalt/Platform/Window.h"
#include "Cobalt/Rendering/Renderer.h"

#include <dwmapi.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace Cobalt
{
	namespace Utils
	{
		COLORREF ColorToCOLORREF(const Color& col)
		{
			u8 r = static_cast<u8>(col.r * 255.0f);
			u8 g = static_cast<u8>(col.g * 255.0f);
			u8 b = static_cast<u8>(col.b * 255.0f);

			return (b << 16) | (g << 8) | r;
		}
	}

	Window::Window(const WindowProperties& properties)
	{
		m_Properties = properties;

		m_Data.Title = properties.Title;
		m_Data.Width = properties.Width;
		m_Data.Height = properties.Height;

		if (!glfwInit())
			LOG_ERROR("Failed to initialize GLFW!");

		LOG_INFO("GLFW initialized");

		switch (Renderer::GetAPI())
		{
			case GraphicsAPI::OpenGL:
			{
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
				glfwWindowHint(GLFW_OPENGL_PROFILE, OPENGL_PROFILE);

				break;
			}
		}

		if (!m_Properties.Resizeable)
		{
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		}

		m_Window = glfwCreateWindow(m_Properties.Width, m_Properties.Height, m_Properties.Title.c_str(), nullptr, nullptr);
		if (m_Window == nullptr)
			LOG_ERROR("Failed to create window!");
		
		LOG_INFO("Window created: Dimensions: {}x{} Title: {}", m_Properties.Width, m_Properties.Height, m_Properties.Title.c_str());

		m_GraphicsContext = GraphicsContext::Create(m_Window);
		m_GraphicsContext->Init();

		HWND hWnd = glfwGetWin32Window(m_Window);

		COLORREF CAPTION_COLOR = Utils::ColorToCOLORREF(m_Properties.CaptionColor);
		COLORREF BORDER_COLOR = Utils::ColorToCOLORREF(m_Properties.BorderColor);

		DwmSetWindowAttribute(hWnd, DWMWINDOWATTRIBUTE::DWMWA_CAPTION_COLOR, &CAPTION_COLOR, sizeof(CAPTION_COLOR));
		DwmSetWindowAttribute(hWnd, DWMWINDOWATTRIBUTE::DWMWA_BORDER_COLOR, &BORDER_COLOR, sizeof(BORDER_COLOR));

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

	void Window::SetWidth(u32 width)
	{
		m_Properties.Width = width;
		glfwSetWindowSize(m_Window, m_Properties.Width, m_Properties.Height);
	}

	void Window::SetHeight(u32 height)
	{
		m_Properties.Height = height;
		glfwSetWindowSize(m_Window, m_Properties.Width, m_Properties.Height);
	}

	void Window::SetTitle(const String& title)
	{
		m_Properties.Title = title;
		glfwSetWindowTitle(m_Window, m_Properties.Title.c_str());
	}

	void Window::SetVsync(bool value)
	{
		m_Properties.Vsync = value;
		glfwSwapInterval((int)value);
	}

	void Window::SetPosition(const Vec2& pos)
	{
		glfwSetWindowPos(m_Window, (int)pos.x, (int)pos.y);
	}

	Vec2 Window::GetPosition()
	{
		int x;
		int y;
		glfwGetWindowPos(m_Window, &x, &y);

		return Vec2(x, y);
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