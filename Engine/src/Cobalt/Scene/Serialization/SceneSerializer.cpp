#include "cbpch.h"

#include "Cobalt/Scene/Serialization/SceneSerializer.h"
#include "Cobalt/Scene/Serialization/Emitter.h"
#include "Cobalt/Scene/Serialization/Parser.h"
#include "Cobalt/Scene/ECS/Entity.h"
#include "Cobalt/Scene/Scene.h"
#include "Cobalt/Logger/Log.h"

namespace Cobalt
{
	void SceneSerializer::Serialize(const char* filepath, const Ref<Scene>& scene)
	{
		CBS::Emitter out(filepath);
		
		out << "Name: " << scene->GetName() << "\n";

		scene->Registry().each([&](auto entityID)
		{
			Entity entity = { entityID, scene.get() };

			out << "Entity:\n";

			auto& tag = entity.GetComponent<TagComponent>();
			out.BeginMap();
			out << "Tag component:\n";

			out.BeginMap();
			out.Add("Tag", tag.Tag);
			out.EndMap();

			auto& transform = entity.GetComponent<TransformComponent>();
			out << "Transform component:\n";
			out.BeginMap();
			out.Add("Position", transform.Position);
			out.Add("Rotation", transform.Rotation);
			out.Add("Scale", transform.Scale);
			out.EndMap();

			if (entity.HasComponent<SpriteRendererComponent>())
			{
				auto& sprite = entity.GetComponent<SpriteRendererComponent>();
				out << "Sprite renderer component:\n";
				out.BeginMap();

				out.Add("Path", sprite.Texture ? sprite.Texture->GetPath() : "null");
				out.Add("Color", sprite.Color);
				out.Add("Tiling", sprite.Tiling);

				out.EndMap();
			}

			out << "\n";
			out.EndMap();
		});

		out.Write();
		LOG_ENGINE_INFO("Scene saved: {}", filepath);
	}

	void SceneSerializer::Deserialize(const char* filepath, const Ref<Scene>& scene)
	{
		scene->ClearEntites();

		std::ifstream file(filepath);
		std::string line;

		std::getline(file, line);
		scene->SetName(CBS::Parser::GetString(line).c_str());

		while (std::getline(file, line))
		{
			if (line.find("Entity") != std::string::npos)
			{
				CBS::Parser::GetEntity(file, scene);
			}
		}
	}
}