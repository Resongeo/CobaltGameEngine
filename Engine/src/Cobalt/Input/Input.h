#pragma once

#include "Cobalt/Core/Core.h"
#include "Cobalt/Core/Math.h"

struct GLFWwindow;

namespace Cobalt
{
	class Input
	{
	public:
		static bool GetKeyDown(int keycode) { return s_Input->GetKeyDownImpl(keycode); }
		static bool GetMouseButtonDown(int button) { return s_Input->GetMouseButtonDownImpl(button); }
		
		static float GetMouseX() { return s_Input->GetMouseXImpl(); }
		static float GetMouseY() { return s_Input->GetMouseYImpl(); }

		static Vec2 GetMousePos() { return s_Input->GetMousePosImpl(); }

	private:
		static void Init();

		bool GetKeyDownImpl(int keycode);
		bool GetMouseButtonDownImpl(int button);
		
		float GetMouseXImpl();
		float GetMouseYImpl();

		Vec2 GetMousePosImpl();

	private:
		static Input* s_Input;
		static GLFWwindow* s_Window;

		friend class Application;
	};
}