#include "Editor/Panels/Particles/ParticleEditorPanel.h"

ParticleEditorPanel::ParticleEditorPanel(const Ref<ParticleSystem>& particleSystem) : EditorPanel("Particle Editor"), m_ParticleSystem(particleSystem)
{
	FramebufferSpecification fbSpecs;
	fbSpecs.Attachments = { FramebufferAttachmentType::RGBA8 };
	fbSpecs.Width = Application::GetWindow()->GetWidth();
	fbSpecs.Height = Application::GetWindow()->GetHeight();
	fbSpecs.Samples = 1;
	m_Framebuffer = Framebuffer::Create(fbSpecs);

	m_EditorCamera = CreateRef<EditorCamera>();
	m_EditorCamera->SetViewportSize(500.0f, 500.0f);
}

void ParticleEditorPanel::Update()
{
	m_Framebuffer->Bind();
	RenderCommand::BeginScene(m_EditorCamera);
	RenderCommand::ClearColor(Color(22));
	RenderCommand::Clear();

	m_ParticleSystem->Update();
	
	RenderCommand::EndScene();
	m_Framebuffer->Unbind();
}

void ParticleEditorPanel::ImGuiUpdate()
{
	ImGui::Begin(GetName());

	ImGui::Image((ImTextureID)m_Framebuffer->GetColorAttachmentID(0), { 500, 500 }, ImVec2{0, 1}, ImVec2{1, 0});

	for (auto& generator : m_ParticleSystem->GetGenerators())
	{
		DisplayGenerator(generator);
	}

	ImGui::End();
}

void ParticleEditorPanel::DisplayGenerator(const Ref<ParticleGenerator>& generator)
{
	switch (generator->Type)
	{
		case ParticleGeneratorType::BoxPosition:
		{
			auto* gen = static_cast<BoxPositionGenerator*>(generator.get());
			
			ImGui::Text("Box Position");
			ImGui::DragFloat2("Min Pos", glm::value_ptr(gen->MinPosition), 0.1f);
			ImGui::DragFloat2("Max Pos", glm::value_ptr(gen->MaxPosition), 0.1f);
			break;
		}
		case ParticleGeneratorType::Lifetime:
		{
			auto* gen = static_cast<LifetimeGenerator*>(generator.get());

			ImGui::Text("Lifetime");
			ImGui::DragFloat("Min", &gen->Min, 0.1f);
			ImGui::DragFloat("Max", &gen->Max, 0.1f);
			break;
		}
		case ParticleGeneratorType::Velocity:
		{
			auto* gen = static_cast<VelocityGenerator*>(generator.get());

			ImGui::Text("Velocity");
			ImGui::DragFloat2("Min Vel", glm::value_ptr(gen->MinDirection), 0.1f);
			ImGui::DragFloat2("Max Vel", glm::value_ptr(gen->MaxDirection), 0.1f);
			break;
		}
	}
}
