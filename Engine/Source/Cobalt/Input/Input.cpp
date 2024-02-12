#include "cbpch.h"

#include "Cobalt/Core/Application.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <imgui.h>

namespace Cobalt
{
	Input* Input::s_Input = nullptr;
	GLFWwindow* Input::s_Window = nullptr;

	void Input::Init()
	{
		s_Window = Application::GetWindow()->GetHandle();
	}

	bool Input::GetKeyDownImpl(int keycode)
	{
		auto state = glfwGetKey(s_Window, keycode);

		return state == GLFW_PRESS;
	}

	bool Input::GetMouseButtonDownImpl(int button)
	{
		auto state = glfwGetMouseButton(s_Window, button);

		return state == GLFW_PRESS;
	}

	bool Input::GetMouseButtonClickedImpl(int button)
	{
		return ImGui::IsMouseClicked(button);
	}

	bool Input::GetMouseButtonReleasedImpl(int button)
	{
		return ImGui::IsMouseReleased(button);
	}

	bool Input::GetMouseButtonDoubleClickedImpl(int button)
	{
		return ImGui::IsMouseDoubleClicked(button);
	}

	float Input::GetMouseXImpl()
	{
		double x, y;
		glfwGetCursorPos(s_Window, &x, &y);

		return (float)x;
	}

	float Input::GetMouseYImpl()
	{
		double x, y;
		glfwGetCursorPos(s_Window, &x, &y);

		return (float)y;
	}

	Vec2 Input::GetMousePosImpl()
	{
		double x, y;
		glfwGetCursorPos(s_Window, &x, &y);

		return Vec2((float)x, (float)y);
	}
}