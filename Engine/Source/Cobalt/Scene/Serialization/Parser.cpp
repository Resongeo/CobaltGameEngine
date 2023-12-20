#include "cbpch.h"

#include "Cobalt/Scene/Serialization/Parser.h"

namespace Cobalt
{
	namespace CBS
	{
		void Parser::CreateEntity(std::ifstream& file, const Ref<Scene>& scene)
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
					tc.Tag = GetString(line);

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
				
				if (line.find("Lua Script component:") != String::npos)
				{
					auto& lsc = entity.AddComponent<LuaScriptComponent>();

					std::getline(file, line);
					lsc.Source = GetString(line);
					lsc.SourceType = LuaScriptSourceType::Filepath;

					continue;
				}

				return;
			}
		}
	}
}