#pragma once

#include "Cobalt.h"
using namespace Cobalt;

namespace CobaltEditor
{
	struct Fonts
	{
		ImFont* Regular;
	};

	class StyleManager
	{
	public:
		static void Init();
		static void LoadFonts();
		static void LoadStyle();

		static Fonts& GetFonts() { return s_Instance->m_Fonts; }

	private:
		static StyleManager* s_Instance;
		Fonts m_Fonts;
	};
}