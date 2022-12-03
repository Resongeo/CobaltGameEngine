#pragma once

#include "Cobalt.h"

#include "Editor/EditorLayer.h"
#include "Editor/Debug/LogLayer.h"

namespace Cobalt
{
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
}