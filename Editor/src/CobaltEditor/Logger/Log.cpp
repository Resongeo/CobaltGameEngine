#include "pch.h"
#include "CobaltEditor/Logger/Log.h"

namespace CobaltEditor
{
	Log* Log::s_Instance = nullptr;

	void Log::Init()
	{
		s_Instance = new Log();
	}
}