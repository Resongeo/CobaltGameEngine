#pragma once

#include "Cobalt/Core/Types.h"

namespace Cobalt
{
	class Scene;

	class SceneSerializer
	{
	public:
		void Serialize(const String& filepath, const Shared<Scene>& scene);
		void Deserialize(const String& filepath, const Shared<Scene>& scene);
	};
}