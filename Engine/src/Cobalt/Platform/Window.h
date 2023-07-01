#pragma once

#include "Cobalt/Core/Core.h"
#include "Cobalt/Events/Event.h"
#include "Cobalt/Events/KeyEvent.h"
#include "Cobalt/Events/MouseEvent.h"
#include "Cobalt/Events/ApplicationEvent.h"
#include "Cobalt/Logger/Log.h"
#include "Cobalt/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Cobalt
{
	struct WindowProperties
	{
		std::string Title = "Cobalt Engine";
		uint32_t Width = 1280;
		uint32_t Height = 720;
		bool Vsync = true;
		bool Resizeable = true;

		WindowProperties() = default;
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

		void SetPosition(const Vec2& pos);
		Vec2 GetPosition();
		
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
			uint32_t Width;
			uint32_t Height;
			bool Vsync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}