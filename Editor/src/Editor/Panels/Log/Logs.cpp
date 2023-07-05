#include "Editor/Panels/Log/Logs.h"

Logs* Logs::s_Instance = nullptr;

void Logs::Init()
{
	s_Instance = new Logs();
}
