#pragma once

#include "Core/Core.h"
#include "Logger/Log.h"

#include "Events/Event.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"

#include "Renderer/GraphicsContext.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

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

		Window(const WindowProperties& properties);

		WindowProperties GetProperties();
		GLFWwindow* GetHandle() const { return m_Window; }

		uint32_t GetWidth() const { return m_Data.Width; }
		uint32_t GetHeight() const { return m_Data.Height; }

		void SetWidth(uint32_t width);
		void SetHeight(uint32_t height);

		void SetTitle(const std::string& title);
		void SetVsync(bool value);
		
		void Update();
		void Destroy();
		
		bool ShouldClose();

		void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }

		static Ref<Window> Create(const WindowProperties& properties = WindowProperties());

	private:
		GLFWwindow* m_Window;
		WindowProperties m_Properties;
		Ref<GraphicsContext> m_GraphicsContext;

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