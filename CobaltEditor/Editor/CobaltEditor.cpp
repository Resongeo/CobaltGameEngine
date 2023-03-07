#include "Editor/CobaltEditor.h"

CobaltEditor* CobaltEditor::s_Instance = nullptr;

CobaltEditor::CobaltEditor(const ApplicationSpecification& applicationSpecification) : Application(applicationSpecification)
{
	s_Instance = this;

	StyleManager::Init();
	Controls::Init();
	EditorPanelManager::Init();

	m_EditorLayer = new EditorLayer();
	PushLayer(m_EditorLayer);
}