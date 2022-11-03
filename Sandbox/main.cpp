#include "Cobalt.h"

int main()
{
	Cobalt::Log::Init();

	Cobalt::Window window;
	
	if (window.Create()) LOG_INFO("Window created succesfully!");

	printf("\nLog tests:\n\n");
	LOG_TRACE("TRACE");
	LOG_INFO("INFO");
	LOG_WARN("WARN");
	LOG_ERROR("ERROR");
	LOG_FATAL("FATAL");

	while (!glfwWindowShouldClose(window.GetHandle()))
	{
		glfwPollEvents();

		glfwSwapBuffers(window.GetHandle());
	}

	window.Destroy();

	return 0;
}