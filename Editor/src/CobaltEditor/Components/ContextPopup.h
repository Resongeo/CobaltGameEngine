#pragma once

#include "Cobalt.h"
using namespace Cobalt;

namespace CobaltEditor
{
	struct MenuItem
	{
		const char* Label;
		std::function<void()> Action;

		MenuItem(const char* label, void (*action)()) : Label(label), Action(action) { }
	};

	class ContextPopup
	{
	public:
		ContextPopup() = default;

		void SetTitle(const char* title);
		void AddMenuItem(const char* label, void (*action)());
		void Open(float width = 200.0f);
		void Close();
		void Toggle(float width = 200.0f);
		void Draw();

	private:
		std::vector<MenuItem> m_MenuItems;
		bool m_Opened = false;
		bool m_HasSpace = true;
		const char* m_Title = "Context Popup";
		float m_Width = 0.0f;
		ImVec2 m_MousePos = { 0, 0 };
		ImVec2 m_Padding = { 5.5, 3 };
	};
}