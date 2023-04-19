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
};