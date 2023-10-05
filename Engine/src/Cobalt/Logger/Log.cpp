#include "cbpch.h"

#include "Cobalt/Logger/Log.h"

namespace Cobalt
{
	Log* Log::s_Instance = nullptr;

	void Log::Init()
	{
		s_Instance = new Log();
	}

	void Log::SetEventCallback(const EventCallbackFn& callback)
	{
		s_Instance->m_EventCallback = callback;
	}
}