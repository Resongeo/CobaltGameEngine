#pragma once

#include "Cobalt.h"
using namespace Cobalt;

#include "Editor/Panels/EditorPanel.h"

class ComponentsPanel : public EditorPanel
{
public:
	ComponentsPanel();

	virtual void Update() override;

private:
	void DrawComponents(Entity entity);
	void DrawVector3(const char* label, glm::vec3& values, float resetValue = 0.0f, float item_width = 80.0f, float speed = 0.05f);
	void DrawVector2(const char* label, glm::vec2& values, float resetValue = 0.0f, float item_width = 120.0f, float speed = 0.05f);
};