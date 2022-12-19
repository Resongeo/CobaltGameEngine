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
	void DrawVector3(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float item_width = 60.0f, float speed = 0.05f);
};