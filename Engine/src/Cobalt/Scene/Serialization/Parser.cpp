#include "cbpch.h"

#include "Cobalt/Scene/Serialization/Parser.h"
#include "Cobalt/Logger/Log.h"

namespace Cobalt
{
	namespace CBS
	{
		void Parser::GetEntity(std::ifstream& file, const Ref<Scene>& scene)
		{
			Entity entity = scene->CreateEntity();
			std::string line;

			while (std::getline(file, line))
			{
				if (line.find("ID component:") != std::string::npos)
				{
					auto& ic = entity.GetComponent<IDComponent>();
					
					std::getline(file, line);
					ic.UUID = GetUUID(line);

					continue;
				}

				if (line.find("Tag component:") != std::string::npos)
				{
					auto& tc = entity.GetComponent<TagComponent>();

					std::getline(file, line);
					tc.Tag = GetString(line);

					continue;
				}
				
				if (line.find("Transform component:") != std::string::npos)
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
				
				if (line.find("Sprite renderer component:") != std::string::npos)
				{
					auto& src = entity.AddComponent<SpriteRendererComponent>();

					std::getline(file, line);
					// TODO: Load textures from asset manager with UUID, for now it gets a default white texture

					std::getline(file, line);
					src.Color = GetVec<4>(ExtractNumbers(line));

					std::getline(file, line);
					src.Tiling = GetVec<2>(ExtractNumbers(line));

					continue;
				}
				
				if (line.find("Lua Script component:") != std::string::npos)
				{
					auto& lsc = entity.AddComponent<LuaScriptComponent>();

					std::getline(file, line);
					lsc.Source = GetString(line);

					continue;
				}

				return;
			}
		}
	}
}