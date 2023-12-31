#include "cbpch.h"

#ifdef _WIN32

#include "Cobalt/Core/Application.h"
#include "Cobalt/Platform/PlatformUtils.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <Windows.h>

namespace Cobalt
{
	void PlatformUtils::RestartApplication()
	{
		HWND windowHandle = glfwGetWin32Window(Application::GetWindow()->GetHandle());
		TCHAR szFileName[MAX_PATH] = {};

		if (!GetModuleFileName(NULL, szFileName, MAX_PATH))
		{
			printf("Cannot install service (%d)\n", GetLastError());
			return;
		}
		ShellExecute(GetDesktopWindow(), NULL, szFileName, NULL, NULL, SW_SHOWDEFAULT);
		Application::Close();
	}
}

#endif // _WIN32
