#include "pch.h"
#include "CobaltEditor/Components/ContextPopup.h"

namespace CobaltEditor
{
	void ContextPopup::SetTitle(const char* title)
	{
		m_Title = title;
	}

	void ContextPopup::AddMenuItem(const char* label, void(*action)())
	{
		m_MenuItems.push_back(MenuItem(label, action));
	}

	void ContextPopup::Open(float width)
	{
		m_MousePos = ImGui::GetMousePos();
		m_HasSpace = m_MousePos.x + width + (m_Padding.x * 2) < Application::GetWindow()->GetPosition().x + Application::GetWindow()->GetWidth();
		m_Width = width;
		m_Opened = true;
	}

	void ContextPopup::Close()
	{
		m_Opened = false;
	}

	void ContextPopup::Toggle(float width)
	{
		if (m_Opened)
		{
			Close();
		}
		else
		{
			Open(width);
		}
	}

	void ContextPopup::Draw()
	{
		ImGui::Begin("Sizes");

		ImGui::DragFloat2("Padding", &m_Padding.x, 0.1f);

		ImGui::End();

		if (!m_Opened) return;

		ImGui::SetNextWindowPos(m_HasSpace ? m_MousePos : ImVec2(m_MousePos.x - (m_Width + m_Padding.x * 2) - 10.f, m_MousePos.y));
		ImGui::SetNextWindowSize({ m_Width + (m_Padding.x * 2), 0});
		ImGui::Begin(m_Title, nullptr, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);

		CursorUtils::Translate({ (ImGui::GetContentRegionMax().x / 2) - (ImGui::CalcTextSize(m_Title).x / 2), m_Padding.y });
		{
			ScopedFont _(StyleManager::GetFonts().SemiBold);
			ImGui::Text(m_Title);
		}

		for (auto& menuItem : m_MenuItems)
		{
			auto cursorPos = ImGui::GetCursorScreenPos();
			ImVec2 min = { cursorPos.x + m_Padding.x, cursorPos.y };
			ImVec2 max = { min.x + m_Width, cursorPos.y + ImGui::GetTextLineHeight() + 12.0f };
			Color bgCol = Color(0, 0);

			if (MouseUtils::Intersect(min, max))
			{
				if (Input::GetMouseButtonClicked(MOUSE_BUTTON_LEFT))
				{
					menuItem.Action();
					Close();
				}

				bgCol = Color(38);
			}

			Shapes::DrawRect(min, max, bgCol, 5.0f);
			CursorUtils::Translate({ m_Padding.x + 10, 6 });
			ImGui::Text(menuItem.Label);
			ImGui::Dummy({ 0, m_Padding.y });
		}
		ImGui::Dummy({ 0, 1 });

		ImGui::End();
	}
}