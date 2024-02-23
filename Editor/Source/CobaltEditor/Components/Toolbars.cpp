#include "pch.h"
#include "CobaltEditor/Components/Toolbars.h"

namespace CobaltEditor
{
	static Shared<Scene> s_PreviousScene = nullptr;

	void Toolbars::Topbar()
	{
		auto scene = SceneManager::GetActiveScene();
		auto window = Application::GetWindow();

		auto viewport = ImGui::GetMainViewport();
		auto topbarHeight = StyleManager::GetSizes().Toolbar.TopbarHeight;
		auto topbarPadding = StyleManager::GetSizes().Toolbar.TopbarPadding;
		auto groupMargin = StyleManager::GetSizes().Toolbar.TopbarGroupMargin;

		auto groupBgCol = StyleManager::GetColors().Toolbar.GroupBackgroundColor;
		auto navigationCol = StyleManager::GetColors().Toolbar.NavigationColor;

		ImGui::SetNextWindowPos({ viewport->Pos.x, viewport->Pos.y });
		ImGui::SetNextWindowSize({ viewport->Size.x, topbarHeight });
		//ImGui::SetNextWindowViewport(viewport->ID);
		ImGuiWindowFlags windowFlags = 0
			| ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoDocking
			| ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse
			| ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoBringToFrontOnFocus;

		ScopedStyleVars _
		({
			{ ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f) },
			{ ImGuiStyleVar_WindowRounding, 0.0f },
			{ ImGuiStyleVar_WindowBorderSize, 0.0f },
		});

		ImGui::Begin("Toolbar-Topbar", NULL, windowFlags);
		{
			auto min = ImGui::GetCursorScreenPos();
			min.x += topbarPadding;
			min.y += topbarPadding;

			auto max = ImVec2(min.x + 68.0f, min.y + topbarHeight - (topbarPadding * 2.0f));

			Shapes::DrawRect(min, max, groupBgCol, 4.0f);

			float buttonSize = topbarHeight - (topbarPadding * 2.0f) - (groupMargin * 2.0f);

			ScopedColor btnBg(ImGuiCol_Button, groupBgCol);
			ScopedColor btnHover(ImGuiCol_ButtonHovered, Color(60));

			{
				ScopedColor _(ImGuiCol_Text, navigationCol);
				CursorUtils::Translate(Vec2(topbarPadding + groupMargin));
				ImGui::Button(ICON_FA_CIRCLE_ARROW_LEFT, { buttonSize, buttonSize });
				ImGui::SameLine();
				ImGui::Button(ICON_FA_CIRCLE_ARROW_RIGHT, { buttonSize, buttonSize });
			}

			min.x = max.x + 6.0f;
			max = ImVec2(min.x + 70.0f, min.y + topbarHeight - (topbarPadding * 2.0f));
			Shapes::DrawRect(min, max, groupBgCol, 4.0f);

			{
				ScopedColor _(ImGuiCol_Text, Color(220));
				ImGui::SameLine();
				CursorUtils::Translate({4, 0});
				ImGui::Button(ICON_FA_PLUS " Scene", {ImGui::CalcTextSize(ICON_FA_PLUS " Scene").x + 6.0f, buttonSize});
			}

			min.x = max.x + 6.0f;
			max = ImVec2(min.x + 120.0f, min.y + topbarHeight - (topbarPadding * 2.0f));
			Shapes::DrawRect(min, max, groupBgCol, 4.0f);

			{
				ImGui::SameLine();
				CursorUtils::Translate({ 4, 0 });
				switch (scene->GetState())
				{
					case SceneState::None:
					case SceneState::Edit:
					{
						ScopedColor _(ImGuiCol_Text, Color(89, 222, 91));
						if (ImGui::Button(ICON_FA_PLAY " Play Scene", { ImGui::CalcTextSize(ICON_FA_PLAY " Play Scene").x + 7.0f, buttonSize }))
						{
							s_PreviousScene = Scene::Copy(scene);

							scene->RuntimeStart();
							scene->SetState(SceneState::Play);

							window->SetBorderColor(Color(222, 89, 89));
						}
						break;
					}
					case SceneState::Play:
					{
						ScopedColor _(ImGuiCol_Text, Color(222, 89, 89));
						if (ImGui::Button(ICON_FA_STOP " Stop Scene", { ImGui::CalcTextSize(ICON_FA_STOP " Stop Scene").x + 7.0f, buttonSize }))
						{
							scene->SetState(SceneState::Edit);
							window->ResetBorderColor();

							SceneManager::SetActiveScene(Scene::Copy(s_PreviousScene));
						}
						break;
					}
					default: break;
				}
			}
		}
		ImGui::End();
	}
}