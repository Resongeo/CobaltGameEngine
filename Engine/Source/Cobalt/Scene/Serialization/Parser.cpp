#include "cbpch.h"

#include "Cobalt/Scene/Serialization/Parser.h"
#include "Cobalt/Scene/ECS/Components.h"

namespace Cobalt
{
	namespace CBS
	{
		void Parser::CreateEntity(std::ifstream& file, const Shared<Scene>& scene)
		{
			Entity entity = scene->CreateEntity();
			String line;

			while (std::getline(file, line))
			{
				if (line.find("ID component:") != String::npos)
				{
					auto& ic = entity.GetComponent<IDComponent>();
					
					std::getline(file, line);
					ic.UUID = GetUUID(line);

					continue;
				}

				if (line.find("Tag component:") != String::npos)
				{
					auto& tc = entity.GetComponent<TagComponent>();

					std::getline(file, line);
					tc.Name = GetString(line);

					continue;
				}
				
				if (line.find("Transform component:") != String::npos)
				{
					auto& tc = entity.GetComponent<TransformComponent>();

					std::getline(file, line);
					tc.Position = GetVec<3>(ExtractNumbers(line));

					std::getline(file, line);
					tc.Rotation = GetVec<3>(ExtractNumbers(line));

					std::getline(file, line);
					tc.Scale = GetVec<3>(ExtractNumbers(line));

					continue;
				}
				
				if (line.find("Sprite renderer component:") != String::npos)
				{
					auto& src = entity.AddComponent<SpriteRendererComponent>();

					std::getline(file, line);
					// TODO: Load textures from asset manager with UUID, for now it gets a default white texture

					std::getline(file, line);
					src.Tint = GetVec<4>(ExtractNumbers(line));

					std::getline(file, line);
					src.Tiling = GetVec<2>(ExtractNumbers(line));

					continue;
				}

				return;
			}
		}
	}
}