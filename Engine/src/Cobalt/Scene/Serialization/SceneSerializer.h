#pragma once

#include "Cobalt/Core/Core.h"

namespace Cobalt
{
	class Scene;

	class SceneSerializer
	{
	public:
		void Serialize(const char* filepath, const Ref<Scene>& scene);
		void Deserialize(const char* filepath, const Ref<Scene>& scene);
	};
}