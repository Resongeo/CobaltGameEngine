#pragma once

#include "Cobalt/Core/Types.h"
#include "Cobalt/Events/Event.h"
#include "Cobalt/Events/KeyEvent.h"
#include "Cobalt/Events/MouseEvent.h"
#include "Cobalt/Events/ApplicationEvent.h"

struct GLFWwindow;

namespace Cobalt
{
	struct WindowProperties
	{
		String Title = "Cobalt Engine";
		u32 Width = 1280;
		u32 Height = 720;
		bool Vsync = true;
		bool Resizeable = true;
		Color CaptionColor = Color(20, 20, 21);
		Color BorderColor = Color(30, 30, 32);

		WindowProperties() = default;
	};

	class Window
	{
	public:
		Window(const WindowProperties& properties);

		WindowProperties GetProperties();
		GLFWwindow* GetHandle() const { return m_Window; }

		u32 GetWidth() const { return m_Data.Width; }
		u32 GetHeight() const { return m_Data.Height; }

		void SetWidth(u32 width);
		void SetHeight(u32 height);

		void SetTitle(const String& title);
		void SetVsync(bool value);

		void SetPosition(const Vec2& pos);
		Vec2 GetPosition();
		
		void Update();
		void Destroy();
		
		bool ShouldClose();

		void SetBorderColor(const Color& color);
		void ResetBorderColor();

		void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }

		static Shared<Window> Create(const WindowProperties& properties = WindowProperties());

	private:
		GLFWwindow* m_Window;
		WindowProperties m_Properties;

		struct WindowData
		{
			String Title;
			u32 Width;
			u32 Height;
			bool Vsync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}