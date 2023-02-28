#pragma once

#include "Cobalt.h"
#include "Editor/Style/Icons.h"

struct EditorFonts
{
	ImFont* Regular;
	ImFont* SemiBold;
};

class StyleManager
{
public:
	static void Init();
	static EditorFonts* GetEditorFonts() { return &s_Instance->m_EditorFonts; }
	
private:
	void LoadFonts();
	void SetupStyle();

private:
	static StyleManager* s_Instance;

	EditorFonts m_EditorFonts{};
};