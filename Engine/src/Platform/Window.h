#pragma once

#include "Core/Core.h"
#include "Log/Log.h"

#include "Events/Event.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "glad/glad.h"

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
		using EventCallbackFn = std::function<void(Event&)>;

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
		void Update();

		inline void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }

	private:
		GLFWwindow* m_Window;
		WindowProperties m_Properties;

		struct WindowData
		{
			std::string Title;
			unsigned int Width;
			unsigned int Height;
			bool Vsync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}