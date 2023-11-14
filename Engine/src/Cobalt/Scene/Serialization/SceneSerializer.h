#pragma once

#include "Cobalt/Core/Core.h"

namespace Cobalt
{
	class Scene;

	class SceneSerializer
	{
	public:
		void Serialize(const std::string& filepath, const Ref<Scene>& scene);
		void Deserialize(const std::string& filepath, const Ref<Scene>& scene);
	};
}