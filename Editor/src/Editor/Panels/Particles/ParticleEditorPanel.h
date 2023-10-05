#pragma once

#include "Editor/Panels/EditorPanel.h"

#include "Cobalt.h"
using namespace Cobalt;

class ParticleEditorPanel : public EditorPanel
{
public:
	ParticleEditorPanel(const Ref<ParticleSystem>& particleSystem);

	void Update() override;
	void ImGuiUpdate() override;

private:
	void DisplayGenerator(const Ref<ParticleGenerator>& generator);

private:
	Ref<Framebuffer> m_Framebuffer;
	Ref<EditorCamera> m_EditorCamera;
	Ref<ParticleSystem> m_ParticleSystem;
};