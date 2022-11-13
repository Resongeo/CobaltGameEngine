#pragma once

#include "Core/Math.h"

namespace Cobalt
{
	class Input
	{
	public:
		static bool GetKeyDown(int keycode) { return s_Input->GetKeyDownImpl(keycode); }

		static bool GetMouseButtonDown(int button) { return s_Input->GetMouseButtonDownImpl(button); }

		static float GetMouseX() { return s_Input->GetMouseXImpl(); }
		static float GetMouseY() { return s_Input->GetMouseYImpl(); }
		static glm::vec2 GetMousePos() { return s_Input->GetMousePosImpl(); }

	private:
		bool GetKeyDownImpl(int keycode);

		bool GetMouseButtonDownImpl(int button);

		float GetMouseXImpl();
		float GetMouseYImpl();
		glm::vec2 GetMousePosImpl();

	private:
		static Input* s_Input;
	};
}