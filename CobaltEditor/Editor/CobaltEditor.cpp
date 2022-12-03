#include "Editor/CobaltEditor.h"

namespace Cobalt
{
	CobaltEditor* CobaltEditor::s_Instance = nullptr;

	CobaltEditor::CobaltEditor(const ApplicationSpecification& applicationSpecification) : Application(applicationSpecification)
	{
		s_Instance = this;

		m_EditorLayer = new EditorLayer();
		PushLayer(m_EditorLayer);
		PushLayer(new LogLayer);
	}
}
