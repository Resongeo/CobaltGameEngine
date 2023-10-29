#pragma once

#include "CobaltEditor/Core/EditorLayer.h"
#include "CobaltEditor/Managers/EditorPanelManager.h"

namespace CobaltEditor
{
	class CobaltEditorApplication : public Cobalt::Application
	{
	public:
		CobaltEditorApplication(const Cobalt::ApplicationSpecification& appSpecs) : Application(appSpecs)
		{
			EditorPanelManager::Init();

			PushLayer(new EditorLayer);
		}
	};
}