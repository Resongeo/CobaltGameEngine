#pragma once

#include "CobaltEditor/Core/EditorLayer.h"
#include "CobaltEditor/Managers/EditorPanelManager.h"
#include "CobaltEditor/Logger/Log.h"

namespace CobaltEditor
{
	class CobaltEditorApplication : public Cobalt::Application
	{
	public:
		CobaltEditorApplication(const Cobalt::ApplicationSpecification& appSpecs) : Application(appSpecs)
		{
			Log::Init();
			EditorPanelManager::Init();

			PushLayer(new EditorLayer);
		}
	};
}