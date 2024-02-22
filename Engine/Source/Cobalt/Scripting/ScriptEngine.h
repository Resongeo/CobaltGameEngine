#pragma once

namespace Cobalt
{
	class ScriptEngine
	{
	public:
		static void Init();

	private:
		static void InitMono();
		static void LoadCoreAssembly();
	};
}