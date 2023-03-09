#include "cbpch.h"

#include "Cobalt/Input/Input.h"

#include "Cobalt/Core/Application.h"
#include <GLFW/glfw3.h>

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

	glm::vec2 Input::GetMousePosImpl()
	{
		double x, y;
		glfwGetCursorPos(s_Window, &x, &y);

		return glm::vec2((float)x, (float)y);
	}
}