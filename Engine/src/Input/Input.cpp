#include "Input/Input.h"

#include "Core/Application.h"
#include "GLFW/glfw3.h"

namespace Cobalt
{
	Input* Input::s_Input = nullptr;

	bool Input::IsKeyDownImpl(int keycode)
	{
		GLFWwindow* window = Application::Get().GetWindow().GetHandle();
		auto state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS;
	}

	bool Input::IsMouseButtonDownImpl(int button)
	{
		GLFWwindow* window = Application::Get().GetWindow().GetHandle();
		auto state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}

	float Input::GetMouseXImpl()
	{
		GLFWwindow* window = Application::Get().GetWindow().GetHandle();
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		return (float)x;
	}

	float Input::GetMouseYImpl()
	{
		GLFWwindow* window = Application::Get().GetWindow().GetHandle();
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		return (float)y;
	}

	glm::vec2 Input::GetMousePosImpl()
	{
		GLFWwindow* window = Application::Get().GetWindow().GetHandle();
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		return glm::vec2((float)x, (float)y);
	}
}