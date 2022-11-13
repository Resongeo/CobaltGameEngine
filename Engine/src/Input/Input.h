#pragma once

#include "Core/Math.h"

namespace Cobalt
{
	class Input
	{
	public:
		static bool IsKeyDown(int keycode) { return s_Input->IsKeyDownImpl(keycode); }

		static bool IsMouseButtonDown(int button) { return s_Input->IsMouseButtonDownImpl(button); }

		static float GetMouseX() { return s_Input->GetMouseXImpl(); }
		static float GetMouseY() { return s_Input->GetMouseYImpl(); }
		static glm::vec2 GetMousePos() { return s_Input->GetMousePosImpl(); }

	private:
		bool IsKeyDownImpl(int keycode);

		bool IsMouseButtonDownImpl(int button);

		float GetMouseXImpl();
		float GetMouseYImpl();
		glm::vec2 GetMousePosImpl();

	private:
		static Input* s_Input;
	};
}