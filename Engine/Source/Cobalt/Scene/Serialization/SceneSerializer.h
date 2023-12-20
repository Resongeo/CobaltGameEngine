#pragma once

#include "Cobalt/Core/Types/Memory.h"
#include "Cobalt/Core/Types/String.h"

namespace Cobalt
{
	class Scene;

	class SceneSerializer
	{
	public:
		void Serialize(const String& filepath, const Ref<Scene>& scene);
		void Deserialize(const String& filepath, const Ref<Scene>& scene);
	};
}