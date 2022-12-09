#pragma once

#include "Cobalt.h"
using namespace Cobalt;

#include "Editor/EditorLayer.h"

class CobaltEditor : public Application
{
public:
	CobaltEditor(const ApplicationSpecification& applicationSpecification);
	~CobaltEditor() {}

	inline EditorLayer* GetEditorLayer() const { return m_EditorLayer; }
	inline static CobaltEditor& Get() { return *s_Instance; }

private:
	static CobaltEditor* s_Instance;

	EditorLayer* m_EditorLayer;
};
