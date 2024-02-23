#include "cbpch.h"

#include "Cobalt/Scene/Serialization/SceneSerializer.h"
#include "Cobalt/Scene/Serialization/Emitter.h"
#include "Cobalt/Scene/Serialization/Parser.h"
#include "Cobalt/Scene/ECS/Components.h"
#include "Cobalt/Scene/ECS/Entity.h"
#include "Cobalt/Scene/Scene.h"

namespace Cobalt
{
	void SceneSerializer::Serialize(const String& filepath, const Shared<Scene>& scene)
	{
		CBS::Emitter out(filepath);
		
		out << "Name: " << scene->GetName() << "\n";

		scene->Registry().each([&](auto entityID)
		{
			Entity entity = { entityID, scene.get() };

			out << "Entity:\n";

			out.BeginMap();

			auto& id = entity.GetComponent<IDComponent>();
			out << "ID component:\n";

			out.BeginMap();
			out.Add("UUID", id.UUID);
			out.EndMap();

			auto& tag = entity.GetComponent<TagComponent>();
			out << "Tag component:\n";

			out.BeginMap();
			out.Add("Tag", tag.Name);
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
				out.Add("Color", (Vec4)sprite.Tint);
				out.Add("Tiling", sprite.Tiling);

				out.EndMap();
			}

			out << "\n";
			out.EndMap();
		});

		out.Write();
		LOG_INFO("Scene saved: {}", filepath);
	}

	void SceneSerializer::Deserialize(const String& filepath, const Shared<Scene>& scene)
	{
		scene->ClearEntites();

		std::ifstream file(filepath);
		String line;

		std::getline(file, line);
		scene->SetName(CBS::Parser::GetString(line).c_str());

		while (std::getline(file, line))
		{
			if (line.find("Entity") != String::npos)
			{
				CBS::Parser::CreateEntity(file, scene);
			}
		}
	}
}