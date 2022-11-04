#pragma once

#include "GLFW/glfw3.h"
#include "Log/Log.h"

namespace Cobalt
{
	struct WindowProperties
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;
		bool Vsync;

		WindowProperties(const std::string& title = "Cobalt Engine", uint32_t width = 1280, uint32_t height = 720, bool vsync = true)
			: Title(title), Width(width), Height(height), Vsync(vsync) {}
	};

	class Window
	{
	public:
		Window(const WindowProperties& properties = WindowProperties());
		bool Create();

		GLFWwindow* GetHandle() const { return m_Window; }
		WindowProperties GetProperties();

		void SetWidth(uint32_t width);
		void SetHeight(uint32_t height);
		void SetTitle(const std::string& title);
		void SetVsync(bool value);
		void Destroy();
		bool ShouldClose();
		void SwapBuffers();

	private:
		GLFWwindow* m_Window;
		WindowProperties m_Properties;
	};
}