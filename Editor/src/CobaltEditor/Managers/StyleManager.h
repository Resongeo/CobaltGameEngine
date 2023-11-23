#pragma once

#include "Cobalt.h"
using namespace Cobalt;

namespace CobaltEditor
{
	struct Fonts
	{
		ImFont* Regular;
	};

	struct SceneHierarchyColors
	{
		Color EvenColor = Color(30, 30, 30);
		Color OddColor = Color(35, 35, 35);
		Color HoverColor = Color(50, 50, 50);
		Color SelectColor = Color(70, 100, 130);
		Color SelectHoverColor = Color(70, 100, 130, 150);
	};

	struct PanelColors
	{
		SceneHierarchyColors SceneHierarchy;
	};

	struct EditorColors
	{
		PanelColors Panels;
	};

	class StyleManager
	{
	public:
		static void Init();
		static void LoadFonts();
		static void LoadStyle();

		static Fonts& GetFonts() { return s_Instance->m_Fonts; }
		static EditorColors& GetColors() { return s_Instance->m_Colors; }

	private:
		static StyleManager* s_Instance;
		Fonts m_Fonts;
		EditorColors m_Colors;
	};
}