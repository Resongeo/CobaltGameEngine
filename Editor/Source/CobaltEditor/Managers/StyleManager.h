#pragma once

#include "Cobalt.h"
using namespace Cobalt;

namespace CobaltEditor
{
	struct Fonts
	{
		ImFont* Regular = nullptr;
		ImFont* SemiBold = nullptr;
		ImFont* IconFont = nullptr;
	};

	struct SceneHierarchyColors
	{
		Color EvenColor = Color(30, 30, 30);
		Color OddColor = Color(35, 35, 35);
		Color HoverColor = Color(50, 50, 50);
		Color SelectColor = Color(70, 100, 130);
		Color SelectHoverColor = Color(70, 100, 130, 150);
	};

	struct ComponentsColors
	{
		Color BackgroundColor = Color(30);
		Color InactiveColor = Color(150, 180);
		Color TransformColor = Color(222, 157, 95);
		Color ScriptColor = Color(133, 214, 124);
		Color SpriteRendererColor = Color(224, 162, 223);
	};

	struct PanelColors
	{
		SceneHierarchyColors SceneHierarchy;
		ComponentsColors Components;
	};

	struct ToolbarColors
	{
		Color GroupBackgroundColor = Color(35);
		Color NavigationColor = Color(88, 151, 214);
	};

	struct EditorColors
	{
		PanelColors Panels;
		ToolbarColors Toolbar;
	};

	struct ToolbarSizes
	{
		float TopbarHeight = 45.0f;
		float TopbarPadding = 6.0f;
		float TopbarGroupMargin = 3.0f;
	};

	struct EditorSizes
	{
		ToolbarSizes Toolbar;
	};

	class StyleManager
	{
	public:
		static void Init();
		static void LoadFonts();
		static void LoadStyle();

		static Fonts& GetFonts() { return s_Instance->m_Fonts; }
		static EditorColors& GetColors() { return s_Instance->m_Colors; }
		static EditorSizes& GetSizes() { return s_Instance->m_Sizes; }

	private:
		static StyleManager* s_Instance;
		Fonts m_Fonts;
		EditorColors m_Colors;
		EditorSizes m_Sizes;
	};
}